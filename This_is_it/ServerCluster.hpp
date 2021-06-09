/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerCluster.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:57:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 12:22:42 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #ifndef SERVERCLUSTER_HPP
// # define SERVERCLUSTER_HPP

// #include "Webserver.hpp"

// class ServerCluster
// {
// 	public:

// 		fd_set readFds;
// 		fd_set writeFds;
	
// 	private:

// 		std::vector< server* >	_servers;
// 		std::map<int, std::map<int, int> > _doublePorts;
// 		int _numberOfServers;
// 		long	highestFd;
	
// 	public:	

// 		ServerCluster();
// 		ServerCluster(ServerCluster const &src);
// 		~ServerCluster();
// 		ServerCluster&		operator=(ServerCluster const &obj);
		
// 		void	addServer(Server *newServer);
// 		bool	isEmpty() const;
		
// 		void	duplicatePorts();
// 		void	startup();
		
		
		
// };
// #endif