/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 15:10:54 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/10 13:58:51 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(int argc, char **argv) : _argc(argc), _argv(argv) {
	return;
}

ConfigParser::ConfigParser(ConfigParser const &src) {
	if (this != &src)
		*this = src;
	return;
}

ConfigParser::~ConfigParser() {
	return;
}

ConfigParser&		ConfigParser::operator=(ConfigParser const &obj)
{
	if (this != &obj) {
		this->_argc = obj._argc;
		this->_argv = obj._argv;
	}
	return *this;
}

std::fstream&	ConfigParser::getConfigFile()
{
	return this->_configFile;
}

void		ConfigParser::openConfigFile()
{
	this->_configFile.open(this->_argv[1]);
	if (!this->_configFile)	{
		throw openFileError("Error: failed to open filepath: ", this->_argv[1]);
	}
}

void		ConfigParser::parseTheConfigFile()
{
	std::string configLine;
	size_t		lineCount = 1;

	while (std::getline(this->_configFile, configLine))
	{
		if (this->_configFile.eof())
			break;
		configLine.erase(std::find(configLine.begin(), configLine.end(), '#'), configLine.end()); // remove comments
		if (Utils::isEmptyLine(configLine))
			continue;
		configLine = Utils::removeLeadingAndTrailingSpaces(configLine);
		if (configLine[0] == '#')
			continue;
		if (configLine != "server {")
		{
			throw parseError(configLine, lineCount);
			return;
		}
		Server	*newServer = new Server;
		
		
			
		
	}
	
}

