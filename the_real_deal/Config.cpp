/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:36:19 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/03 10:55:39 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(std::string defaultServer)
{
	try
	{
		ConfigServer::_initDefaultServer(defaultServer.c_str());
		
	}
	catch(ConfigFileReader::NotAValidFileException& e)
	{
		std::cerr << "Error: Failed to open default.config file\n";
		std::cerr << "Check path" << std::endl;
	}
	
}

Config::Config(Config const &src)
{
	if (this != &src)
		*this = src;
	return;
		
}

Config	&Config::operator=(Config const &src) {
	if (this != &src)
		this->_servers = src._servers;
	return (*this);
}

Config::~Config(void)
{
	return;
}

int		Config::parseConfigFile(const char *configFilePath)
{
	configFileVector	configFileElements;
	size_t				configFileElementsSize;

	// vector of strings that contains all the elements from the config file
	configFileElements = ConfigFileReader::readConfigFile(configFilePath);
	configFileElementsSize = configFileElements.size();
	for (size_t i = 0; i < configFileElementsSize; i++)
	{
		if (configFileElements[i] == "server")
		{
			ConfigServer server; // create a new server
			++i;
			if (configFileElements[i] != "{")
			{
				throw MissingBrackedAfterDirective();
				return 1;
			}
			++i;
			if (!server.serverBlockParser(i, configFileElements))
			{
				throw ErrorInServerParsing();
				return 1;
			}
			this->_servers.push_back(server);
		}
		else
		{
			std::cerr << "Error: missing server directive, failed on: ["<< configFileElements[i] << "]" << std::endl;
			return 1;
		}
	}
	return 0;
}

const char	*Config::MissingBrackedAfterDirective::what() const throw()
{
	return "Error: expected '{' after server directive";
}

const char	*Config::ErrorInServerParsing::what() const throw()
{
	return "Error: server block is incorrect";
}