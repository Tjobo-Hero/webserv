/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:45 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/09 18:08:31 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerCluster.hpp"
#include "./Utils/Utils.hpp"
#include "Request.hpp"

Connection	*g_recentConnection;

ServerCluster::ServerCluster() : _numberOfServers(0), _highestFD(0) {
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	return;
}

ServerCluster::ServerCluster(ServerCluster const &src) {
	if (this != &src)
		*this = src;
	return;
}

ServerCluster::~ServerCluster() {

	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (; this->_allServers.empty() && it != this->_allServers.end(); ++it) {
		delete(*it);
	}
	return;
}

ServerCluster&		ServerCluster::operator=(ServerCluster const &obj) {
	if (this != &obj) {
		this->_numberOfServers = obj._numberOfServers;
		this->_allServers = obj._allServers;
		this->_doublePorts = obj._doublePorts;
		this->_highestFD = obj._highestFD;
		this->readFds = obj.readFds;
		this->writeFds = obj.writeFds;
	}
	return *this;
}

void			ServerCluster::addServer(Server *newServer) {
	this->_allServers.push_back(newServer);
}

bool			ServerCluster::clusterIsEmpty() const {
	return this->_allServers.empty();
}

//TODO checken wat dit doet en of het werkt met meerdere Severs die dezelfde port grebruiken
void	ServerCluster::checkForDuplicatePorts() {
	std::vector<Server*>::iterator it1 = this->_allServers.begin();
	std::vector<Server*>::iterator it2;

	for (; it1 != this->_allServers.end(); ++it1)
	{
		it2 = it1;
		++it2;
		for (; it2 != this->_allServers.end(); ++it2)
			if ((*it1)->getPortNumber() == (*it2)->getPortNumber())
				(*it1)->setAlternativeServers(*it2);
	}
}

void	ServerCluster::setReady()
{
	if (_allServers.size() > 1)
		checkForDuplicatePorts();
	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (; !this->_allServers.empty() && it != this->_allServers.end(); ++it)
	{
		(*it)->startListening();
		FD_SET((*it)->getSocketFD(), &this->readFds);
		this->_highestFD = std::max(this->_highestFD, (*it)->getSocketFD());
		this->_numberOfServers += 1;
	}
}

void	ServerCluster::startListening() {
	while (true)
	{
		fd_set	readSet;
		fd_set	writeSet;
		int		ret;
		long	maxFD= this->_highestFD;
		std::vector<Server*>::iterator it = this->_allServers.begin();
		g_recentConnection = NULL;
		signal(SIGPIPE, Utils::signalHandler); // if we're trying to read or write to a socket that's no longer valid
		FD_ZERO(&writeSet);
		FD_ZERO(&readSet);
		readSet = this->readFds;
		while (it != this->_allServers.end()) {
			for (int i = 0; i < NR_OF_CONNECTIONS; ++i) {
				if ((*it)->connections[i].getAcceptFD() != -1) {
					unsigned long a = Utils::getTime();
					unsigned long b = (*it)->connections[i].getTimeLastRead();
					if (CONNECTION_TIMEOUT > 0 && a - b > CONNECTION_TIMEOUT) {
						if (!(*it)->connections[i].getBuffer().empty()) {
							g_recentConnection = &((*it)->connections[i]);
							(*it)->createResponse(i);
							(*it)->connections[i].sendData((*it)->_bodylen);
						}
						(*it)->connections[i].resetConnection();
						(*it)->connections[i].closeConnection();
						continue;
					}
					maxFD = std::max(maxFD, (*it)->connections[i].getAcceptFD());
					if (!(*it)->connections[i].hasFullRequst())
						FD_SET((*it)->connections[i].getAcceptFD(), &readSet);
					else {
						FD_SET((*it)->connections[i].getAcceptFD(), &writeSet);
						if (!(*it)->connections[i].myResponse)
							(*it)->createResponse(i);
					}
				}
			}
			it++;
		}
		struct timeval timeout;
		timeout.tv_sec = SELECT_TIMEOUT;
		timeout.tv_usec = 0;
		if ((ret = select(maxFD + 1, &readSet, &writeSet, NULL, &timeout)) == -1)
			exit(1); // check trhow
		for (it = this->_allServers.begin(); it != this->_allServers.end() && ret; it++) {
			long fd;
			fd = (*it)->getSocketFD();
			if (FD_ISSET(fd, &readSet)) {
				if ((*it)->acceptConnections() == 1)
					break;
			}
			static int connectionCounter = 0;
			for (int i = 0; i < NR_OF_CONNECTIONS; i++) {
				if ((*it)->connections[connectionCounter].getAcceptFD() != -1) {
					fd = (*it)->connections[connectionCounter].getAcceptFD();
					if (FD_ISSET(fd, &readSet)) {
						g_recentConnection = &((*it)->connections[connectionCounter]);
						(*it)->connections[connectionCounter].startReading();
						break;
					}
					if (FD_ISSET(fd, &writeSet)) {
						g_recentConnection = &((*it)->connections[connectionCounter]);
						if ((*it)->connections[connectionCounter].getResponseString().empty())
							(*it)->setupResponseString(connectionCounter);
						(*it)->connections[connectionCounter].sendData((*it)->_bodylen);
						break;
					}
				}
				connectionCounter++;
				connectionCounter %= NR_OF_CONNECTIONS;
			}
		}
	}
}