/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:47:12 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:53:42 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
	return;
}

Server::~Server() {
	return;
}

Server::Server(Server const &src)
{
	if (this != &src)
		*this = src;
	return;
}

Server&		Server::operator=(Server const &obj)
{
	if (this != &obj)
		std::cout << "asdf" << std::endl;
	return *this;
}

void		Server::configFileParser(const char* configFilePath)
{
	ConfigParser::parseTheConfigFile(configFilePath, this->_allServers);
}