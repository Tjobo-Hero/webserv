/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/22 12:05:49 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLUSTER_HPP
# define SERVERCLUSTER_HPP

# define SELECT_TIMEOUT 2

#include "Webserver.hpp"
#include "Server.hpp"
#include "ConnectionUtils.hpp"

class ServerCluster
{
	public:

		fd_set readFds;
		fd_set writeFds;
	
	private:

		std::vector< Server* >	_allServers;
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
		
		void	checkDuplicatePorts();
		void	startup();
		void	startListening();
};
#endif