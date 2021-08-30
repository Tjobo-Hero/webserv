/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   UtilsServerCluster.hpp                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 10:43:09 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/30 11:24:35 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILSSERVERCLUSTER_HPP
# define UTILSSERVERCLUSTER_HPP
# include "../ServerCluster.hpp"

class ServerCluster;
class Server;

class UtilsServerCluster
{
	public:
	fd_set 	readSet;
	fd_set	writeSet;
		void	makeReadyForListening(ServerCluster &sc, fd_set &readSet, fd_set &writeSet);
		void	setMaxFD(ServerCluster &sc);
		void	checkForDuplicatePorts(ServerCluster &sc);
		// void	setReady();
		void	setupEveryServerInCluster(ServerCluster &sc);
		void	setFD(Server *server, fd_set &fdset);
		void	setHighestFD(ServerCluster &sc, Server *server);

};

#endif
