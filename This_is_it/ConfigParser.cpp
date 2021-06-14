/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 15:10:54 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/14 12:21:33 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(int argc, char **argv) : _argc(argc), _argv(argv) _lineCount(0) {
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

int			ConfigParser::getLineCount() {
	return _lineCount;
}

void		ConfigParser::openConfigFile()
{
	this->_configFile.open(this->_argv[1]);
	if (!this->_configFile)	{
		throw openFileError("Error: failed to open filepath: ", this->_argv[1]);
	}
}

Location*	ConfigParser::getLocation(std::string &startline)
{
	std::string configLine;
	std::string locationPath;;

	locationPath = Utils::checkLocationPath(startline);
	Location *newLocation = new Location(locationPath);
	while (std::getline(this->_configFile, configLine))
	{
		++this->_lineCount;
		if (this->_configFile.eof())
		{
			throw parseError("file is EOF", "what to do?");
			return;
		}
		if (Utils::isEmptyLine(configLine));
			continue;
		if (configLine[0] == '#')
			continue;
		configLine = Utils::removeLeadingAndTrailingSpaces(configLine);
		if (configLine == "server {" || Utils::findFirstWord(configLine) == "location")
		{
			throw parseError(configLine, this->_lineCount);
			return;
		}
		if (configLine == "}")
			break;
		try {
			std::string key = Utils::findFirstWord(configLine);
			newLocation->findKey(key, configLine);
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return;
		}
		if (!newLocation->parameterCheck())
		{
			throw parseError(configLine, this->_lineCount);
			return;
		}
		return (newLocation);
	}
}

void		ConfigParser::parseTheConfigFile(ServerCluster *serverCluster)
{
	std::string configLine;

	while (std::getline(this->_configFile, configLine))
	{
		this->_lineCount++;
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
			throw parseError(configLine, this->_lineCount);
			return;
		}
		Server	*newServer = new Server;
		while (std::getline(this->_configFile, configLine))
		{
			this->_lineCount++;
			if (this->_configFile.eof())
			{
				throw parseError(configLine, this->_lineCount);
				return;
			}
			configLine.erase(std::find(configLine.begin(), configLine.end(), '#'), configLine.end()); // remove comments
			if (Utils::isEmptyLine(configLine))
				continue;
			if (configLine[0] == '#')
				continue;
			configLine = Utils::removeLeadingAndTrailingSpaces(configLine);
			if (Utils::findFirstWord(configLine) == "location")
			{
				Location *newLocation = getLocation(configLine);
				newServer->addLocation(newLocation);
			}
			else if (configLine == "}")
				break;
			else
			{
				try
				{
					std::string key = Utils::findFirstWord(configLine);
					newServer->findKey(key, configLine);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
					return;
				}
				
			}
			
		}
		std::vector<Location*> allLocations = newServer->getLocations();
		std::vector<Location*>::iterator it = allLocations.begin();
		for (; it != allLocations.end(); ++it)
		{
			if (!(*it)->getOwnAutoIndex())
			{
				if (newServer->getAutoIndex())
					(*it)->setAutoIndex("on");
				else
					(*it)->setAutoIndex("off");
			}
			if (!(*it)->getOwnBodySize())
			{
				std::stringstream ss;
				ss << newServer->getMaxBodySize();
				(*it)->setMaxBodySize(ss.str());
			}
		}
		if (!newServer->parameterCheck())
		{
			throw parseError("Paramater check failed", this->_lineCount);
			return;
		}
		serverCluster->addServer(newServer);
	}
	if (serverCluster->clusterIsEmpty())
	{
		throw clusterError("Cluster seems to be empty", "check your input");
		return;
	}
}

