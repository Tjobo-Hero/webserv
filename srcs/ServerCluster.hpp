/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/11 14:39:42 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLUSTER_HPP
# define SERVERCLUSTER_HPP

# define SELECT_TIMEOUT 2

#include "Server.hpp"
#include "Libraries.hpp"
#include "Webserver.hpp"

class Server;

class ServerCluster
{
	private:
		fd_set								readFds;
		fd_set								writeFds;
		std::vector<Server*>				_allServers;
		std::map<int, std::map<int, int> >	_doublePorts;
		long								_highestFD;
		long								_maxFD;

	public:

		ServerCluster();
		ServerCluster(ServerCluster const &src);
		~ServerCluster();
		ServerCluster&		operator=(ServerCluster const &obj);

		void	addServer(Server *newServer);
		bool	clusterIsEmpty() const;

		void	checkForDuplicatePorts();
		void	setReady();
		void	setupEveryServerInCluster();
		void	setFD(Server *server, fd_set &fdset);
		void	setHighestFD(Server *server);
		// void	plusNumberOfServers();

		void	listening();
		void	makeReadyForListening(fd_set &readSet, fd_set &writeSet);
		void	setMaxFD();
		void	connectToServers(fd_set &readSet, fd_set &writeSet);
		void	connections(Server *server, fd_set &readSet, fd_set &writeSet);

		int		checkServerConnection(Server *server, const int i);
		void	setFDForRightConnection(Server *server, int i, fd_set &readSet, fd_set &writeSet);
		int		bufferExists(Connection &connection);
		void	createResponseAndSendData(Server *server, int i);
		void	resetAndCloseConnections(Connection &connection);

		int	readyFD(fd_set &readSet, fd_set &writeSet);
		void	acceptConnectionsInServers(fd_set &readSet, fd_set &writeSet);
		bool	fdIsReady(Server *server, fd_set &readSet);
		void	numberOfConnectionsInServer(Server *server, fd_set &readSet, fd_set &writeSet);

};
#endif