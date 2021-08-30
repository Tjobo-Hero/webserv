/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   UtilsServerCluster.hpp                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 10:43:09 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/30 11:52:41 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILSSERVERCLUSTER_HPP
# define UTILSSERVERCLUSTER_HPP
# include "../ServerCluster.hpp"
// # include "../"

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
