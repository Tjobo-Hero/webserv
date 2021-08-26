/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   makeReadyForListening.cpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 11:01:18 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/13 12:30:12 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "UtilsServerCluster.hpp"

void	UtilsServerCluster::setMaxFD(ServerCluster &sc)
{
	sc._maxFD = sc._highestFD;
}

void	UtilsServerCluster::makeReadyForListening(ServerCluster &sc, fd_set &readSet, fd_set &writeSet)
{
	setMaxFD(sc);
	signal(SIGPIPE, Utils::signalHandler);
	g_recentConnection = NULL;
	FD_ZERO(&writeSet);
	FD_ZERO(&readSet);
	readSet = sc.readFds;
}

void	UtilsServerCluster::checkForDuplicatePorts(ServerCluster &sc)
{
	std::vector<Server*>::iterator it1 = sc._allServers.begin();
	std::vector<Server*>::iterator it2;

	for (; it1 != sc._allServers.end(); ++it1)
	{
		it2 = it1;
		++it2;
		for (; it2 != sc._allServers.end(); ++it2)
			if ((*it1)->getPortNumber() == (*it2)->getPortNumber())
				(*it1)->setAlternativeServers(*it2);
	}
}

void	UtilsServerCluster::setHighestFD(ServerCluster &sc, Server *server)
{
	sc._highestFD = std::max(sc._highestFD, server->getSocketFD());
}

void	UtilsServerCluster::setFD(Server *server, fd_set &fdset)
{
	FD_SET(server->getSocketFD(), &fdset);
}

void	UtilsServerCluster::setupEveryServerInCluster(ServerCluster &sc)
{
	std::vector<Server*>::iterator it = sc._allServers.begin();
	for (; !sc._allServers.empty() && it != sc._allServers.end(); ++it)
	{
		(*it)->setServer();
		setFD(*it, sc.readFds);
		setHighestFD(sc, *it);
	}
}