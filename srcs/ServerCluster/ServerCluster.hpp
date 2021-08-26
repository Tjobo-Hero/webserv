/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/13 12:41:32 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLUSTER_HPP
# define SERVERCLUSTER_HPP

# define SELECT_TIMEOUT 2

#include "../Server.hpp"
#include "../Connection.hpp"
#include "../Libraries.hpp"
#include "../Webserver.hpp"
#include "Utils/UtilsServerCluster.hpp"


class Server;
class Connection;
class UtilsServerCluster;

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

		void	listening();;
		void	connectToServers(UtilsServerCluster &utils);
		void	connections(Server *server, fd_set &readSet, fd_set &writeSet);

		int		checkServerConnection(Server *server, const int i);
		void	setFDForRightConnection(Server *server, int i, fd_set &readSet, fd_set &writeSet);
		int		bufferExists(Connection &connection);
		void	createResponseAndSendData(Server *server, int i);
		void	resetAndCloseConnections(Connection &connection);

		int		isFDReady(fd_set &readSet, fd_set &writeSet);
		void	acceptConnectionsInServers(fd_set &readSet, fd_set &writeSet);
		bool	serverAcceptConnections(Server *server, fd_set &readSet);
		void	serverConnections(Server *server, fd_set &readSet, fd_set &writeSet);
		int		checkActiveServerConnection(const Connection &connection);
		int		startReading(Connection &connection);
		int		setupResponseAndSendData(Server *server, const int connectionCounter);
		friend	class UtilsServerCluster;

};
#endif