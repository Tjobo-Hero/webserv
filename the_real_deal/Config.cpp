/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:36:19 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 12:14:53 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "ConfigServer.hpp"

Config::Config(std::string defaultServer)
{
	try
	{
		ConfigServer::_initDefaultServer(defaultServer.c_str());
		
	}
	catch(ConfigReader::NotAValidFileException& e)
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


int		Config::parse(const char *config_file)
{
	configVector	elements;
	size_t			elementsSize;

	// vector of strings that contains all the elements from the config file
	elements = ConfigReader::readfile(config_file);
	elementsSize = elements.size();
	for (size_t i = 0; i < elementsSize; i++)
	{
		if (elements[i] == "server")
		{
			ConfigServer server; // create a new server
			++i;
			if (elements[i] != "{")
			{
				throw MissingBrackedAfterDirective();
				return 1;
			}
			++i;
			if (!server.serverParser(i, elements))
			{
				throw ErrorInServerParsing();
				return 1;
			}
			this->_servers.push_back(server);
		}
		else
		{
			std::cerr << "Error: missing server directive, failed on: ["<< elements[i] << "]" << std::endl;
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