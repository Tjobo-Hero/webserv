/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:47:14 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 13:02:56 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Webserver.hpp"
#include "ConfigParser.hpp"
#include "ServerBlock.hpp"
#include "ServerConfiguration.hpp"

class Server
{

	public:
		
		// typdef Client			_client
		typedef std::string		ipPort;
		typedef std::vector<ServerBlock>	serverBlocks;
		typedef	std::map<ipPort, serverBlocks>	allServers;
		typedef int	port;
		// typedef std::map<int, Client>	_allClients;
		
		
		// typedef ServerBlock		_serverBlock;
		
		explicit Server();
		Server(Server const &src);
		~Server();

		Server&		operator=(Server const &obj);

		void		configFileParser(char const *configFilePath);
		
	private:
		
		allServers		_allServers;
		
};

#endif