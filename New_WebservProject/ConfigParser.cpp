/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:50:00 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 13:00:41 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(){
	return;
}

ConfigParser::ConfigParser(ConfigParser const &src)
{
	if (this != &src)
		*this = src;
}

ConfigParser::~ConfigParser(){
	return;
}

ConfigParser&		ConfigParser::operator=(ConfigParser const &obj)
{
	if (this != &obj)
		std::cout << "HOI" <<std::endl;
	return *this;
}

int				ConfigParser::openConfigFile(const char* configFilePath)
{
	int						configFileFD;
	
	if ((configFileFD = open(configFilePath, O_RDONLY)) < 0) {
		throw ConfigParser::NotAValidFileException();
	}
	return configFileFD;
}
void			ConfigParser::parseTheConfigFile(const char* configFilePath, Server::allServers &_allServers)
{
	fields fields(2);
	configTokens	tokens;
	// int context = MAIN_CONTEXT;
	// size_t n = 0;
	std::string line;
	(void)_allServers;
	
	int configFileFD = openConfigFile(configFilePath);
	
	std::cout << configFileFD << std::endl;
	
	
	
	
}

const char	*ConfigParser::NotAValidFileException::what() const throw()
{
	std::perror("Failed to open file: ");
	return NULL;
}
