/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/10 09:27:07 by rbraaksm      ########   odam.nl         */
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
	public:

		fd_set readFds;
		fd_set writeFds;

	private:

		std::vector<Server*>	_allServers;
		std::map<int, std::map<int, int> > _doublePorts;
		int _numberOfServers;
		long	_highestFD;

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

		void	startListening();

};
#endif