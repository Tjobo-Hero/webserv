/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:26 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 11:40:43 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

parseMap ConfigServer::_initServerMap() {
		    parseMap	myMap;
		    // myMap["listen"] = &ConfigServer::addListen;
		    myMap["root"] = &ConfigServer::setRoot;
		    // myMap["server_name"] = &ConfigServer::addServerName;
		    // myMap["error_page"] = &ConfigServer::addErrorPage;
		    // myMap["client_body_buffer_size"] = &ConfigServer::addClientBodyBufferSize;
			// myMap["cgi_param"] = &ConfigServer::addCgiParam;
			// myMap["cgi_pass"] = &ConfigServer::addCgiPass;
			// myMap["allow_methods"] = &ConfigServer::addAllowedMethods;
			// myMap["index"] = &ConfigServer::addIndex;
			// myMap["autoindex"] = &ConfigServer::addAutoIndex;
		    return myMap;
}

parseMap ConfigServer::serverParsingMap = ConfigServer::_initServerMap();

int		ConfigServer::serverParser(size_t &index, configVector &elements)
{
	configVector		args;
	parseMap::iterator	it;
	std::string			directive;

	for (; index < elements.size() && elements[index] != "}"; ++index)
	{
		if ((it = ConfigServer::serverParsingMap.find(elements[index])) == ConfigServer::serverParsingMap.end())
		{
			break ;	
		}
		std::cout << "it: " << it->first << std::endl;
		
	}
	return 0;
	
}

void        ConfigServer::setRoot(std::vector<std::string> args) {
	if (args.size() != 1 || this->_root != "")
		throw ConfigServer::ExceptionInvalidArguments();
	this->_root = args[0];
}