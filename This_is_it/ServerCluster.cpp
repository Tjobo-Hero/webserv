/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:45 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/14 12:18:42 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerCluster.hpp"

ServerCluster::ServerCluster() : _numberOfServers(0), _highestFD(0)
{
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

ServerCluster&		ServerCluster::operator=(ServerCluster const &obj)
{
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