/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerBlock.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:18:24 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:48:30 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERBLOCK_HPP
# define SERVERBLOCK_HPP

#include "Webserver.hpp"
#include "ServerConfiguration.hpp"

class ServerBlock
{
	private:

	ServerBlock(void);

	public:

	~ServerBlock(void);
	ServerBlock&	operator=(ServerBlock const &obj);
	
	typedef	ServerConfiguration::directives	_directives;
	typedef ServerConfiguration::allRoutes _allRoutes;
	// typedef Request

	friend class Server;
	friend class Client;
	friend class ConfigParser;
	friend class CGI;

	
	explicit 	ServerBlock(ServerConfiguration serverConfiguration);
	void		initializeServer(void);
	void		closeServer(void);
	_allRoutes::iterator getLocation(std::string const &path);

	private:	

		void setAddress(void);
		std::string &_host;
		std::string _port;
		int	_socket;
		ServerConfiguration _configuration;
		struct sockaddr_in	_sockaddr; 	
	
};
#endif