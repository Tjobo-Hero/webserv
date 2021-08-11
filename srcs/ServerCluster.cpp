/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:45 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/11 18:16:09 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerCluster.hpp"
#include "./Utils/Utils.hpp"
#include "Request.hpp"

Connection	*g_recentConnection;

ServerCluster::ServerCluster() : _highestFD(0)
{
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	return;
}

ServerCluster::ServerCluster(ServerCluster const &src)
{
	if (this != &src)
		*this = src;
	return;
}

ServerCluster::~ServerCluster()
{

	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (; this->_allServers.empty() && it != this->_allServers.end(); ++it)
		delete(*it);
	return;
}

ServerCluster&		ServerCluster::operator=(ServerCluster const &obj)
{
	if (this != &obj)
	{
		this->_allServers = obj._allServers;
		this->_doublePorts = obj._doublePorts;
		this->_highestFD = obj._highestFD;
		this->readFds = obj.readFds;
		this->writeFds = obj.writeFds;
		this->_maxFD = obj._maxFD;
	}
	return *this;
}

void	ServerCluster::addServer(Server *newServer)
{
	this->_allServers.push_back(newServer);
}

bool	ServerCluster::clusterIsEmpty() const
{
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

void	ServerCluster::setHighestFD(Server *server)
{
	this->_highestFD = std::max(this->_highestFD, server->getSocketFD());
}

void	ServerCluster::setFD(Server *server, fd_set &fdset)
{
	FD_SET(server->getSocketFD(), &fdset);
}

void	ServerCluster::setupEveryServerInCluster()
{
	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (; !this->_allServers.empty() && it != this->_allServers.end(); ++it)
	{
		(*it)->setServer();
		setFD(*it, this->readFds);
		setHighestFD(*it);
	}
}

void	ServerCluster::setReady()
{
	if (_allServers.size() > 1)
		checkForDuplicatePorts();
	setupEveryServerInCluster();
}

void	ServerCluster::setMaxFD(void)
{
	this->_maxFD = this->_highestFD;
}

void	ServerCluster::makeReadyForListening(fd_set &readSet, fd_set &writeSet)
{
	setMaxFD();
	signal(SIGPIPE, Utils::signalHandler); // if we're trying to read or write to a socket that's no longer valid
	g_recentConnection = NULL;
	FD_ZERO(&writeSet);
	FD_ZERO(&readSet);
	readSet = this->readFds;
}

int		ServerCluster::bufferExists(Connection &connection)
{
	return connection.getBuffer().empty();
}

void	ServerCluster::createResponseAndSendData(Server *server, int i)
{
	g_recentConnection = &(server->connections[i]);
	server->createResponse(i);
	server->connections[i].sendData(server->_bodylen);
}

void	ServerCluster::resetAndCloseConnections(Connection &connection)
{
	connection.resetConnection();
	connection.closeConnection();
}

int		ServerCluster::checkServerConnection(Server *server, const int i)
{
	if (server->connections[i].getAcceptFD() == -1)
		return 0;
	unsigned long realTime = Utils::getTime();
	unsigned long lastReadTime = server->connections[i].getTimeLastRead();
	if (CONNECTION_TIMEOUT > 0 && realTime - lastReadTime > CONNECTION_TIMEOUT)
	{
		if (bufferExists(server->connections[i]))
			createResponseAndSendData(server, i);
		resetAndCloseConnections(server->connections[i]);
		return 0;
	}
	return 1;
}

void	ServerCluster::setFDForRightConnection(Server *server, int i, fd_set &readSet, fd_set &writeSet)
{
	this->_maxFD = std::max(this->_maxFD, server->connections[i].getAcceptFD());
	if (!server->connections[i].hasFullRequst())
		FD_SET(server->connections[i].getAcceptFD(), &readSet);
	else
	{
		FD_SET(server->connections[i].getAcceptFD(), &writeSet);
		if (!server->connections[i].myResponse)
			server->createResponse(i);
	}
}

void	ServerCluster::connections(Server *server, fd_set &readSet, fd_set &writeSet)
{
	for (int i = 0; i < NR_OF_CONNECTIONS; ++i)
	{
		if (checkServerConnection(server, i) == 1)
			setFDForRightConnection(server, i, readSet, writeSet);
	}
}

void	ServerCluster::connectToServers(fd_set &readSet, fd_set &writeSet)
{
	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (; it != this->_allServers.end(); ++it)
		connections(*it, readSet, writeSet);
}

int		ServerCluster::isFDReady(fd_set &readSet, fd_set &writeSet)
{
	struct timeval timeout;
	timeout.tv_sec = SELECT_TIMEOUT;
	timeout.tv_usec = 0;
	int ret = select(this->_maxFD + 1, &readSet, &writeSet, NULL, &timeout);
	if (ret == -1)
		exit(1);
	return ret;
}

bool	ServerCluster::serverAcceptConnections(Server *server, fd_set &readSet)
{
	long socketFD = server->getSocketFD();
	if (FD_ISSET(socketFD, &readSet))
		if (server->acceptConnections() == 1)
			return false;
	return true;

}

int		ServerCluster::checkActiveServerConnection(const Connection &connection)
{
	return connection.getAcceptFD();
}

int		ServerCluster::startReading(Connection &connection)
{
	g_recentConnection = &connection;
	connection.startReading();
	return 1;
}

int		ServerCluster::setupResponseAndSendData(Server *server, const int connectionCounter)
{
	g_recentConnection = &(server->connections[connectionCounter]);
	if (server->connections[connectionCounter].getResponseString().empty())
		server->setupResponseString(connectionCounter);
	server->connections[connectionCounter].sendData(server->_bodylen);
	return 1;
}

void	ServerCluster::serverConnections(Server *server, fd_set &readSet, fd_set &writeSet)
{
	long fd;
	static int connectionCounter = 0;
	for (int i = 0; i < NR_OF_CONNECTIONS; i++)
	{
		if ((fd = checkActiveServerConnection(server->connections[connectionCounter])) != -1)
		{
			if (FD_ISSET(fd, &readSet))
				if (startReading(server->connections[connectionCounter]))
					break ;
			if (FD_ISSET(fd, &writeSet))
				if (setupResponseAndSendData(server, connectionCounter))
					break ;
		}
		connectionCounter++;
		connectionCounter %= NR_OF_CONNECTIONS;
	}
}

void	ServerCluster::acceptConnectionsInServers(fd_set &readSet, fd_set &writeSet)
{
	std::vector<Server*>::iterator it = this->_allServers.begin();
	for (it = this->_allServers.begin(); it != this->_allServers.end(); it++)
	{
		if (serverAcceptConnections(*it, readSet) == false)
			break ;
		serverConnections(*it, readSet, writeSet);
	}
}

void	ServerCluster::listening()
{
	while (true)
	{
		fd_set	readSet;
		fd_set	writeSet;
		makeReadyForListening(readSet, writeSet);
		connectToServers(readSet, writeSet);
		if (isFDReady(readSet, writeSet))
			acceptConnectionsInServers(readSet, writeSet);
	}
}