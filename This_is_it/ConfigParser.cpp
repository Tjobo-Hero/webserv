/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 15:10:54 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/15 16:30:58 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(int argc, char **argv) : _argc(argc), _argv(argv) {
	this->_lineCount = 0;
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

Location*	ConfigParser::getLocation(std::string &startline)
{
	std::string configLine;
	std::string locationPath;

	locationPath = Utils::checkLocationPath(startline, this->_lineCount);
	Location *newLocation = new Location(locationPath);
	while (std::getline(this->_configFile, configLine))
	{
		++this->_lineCount;
		if (this->_configFile.eof())
			throw parseError("end of file ", this->_lineCount);
		if (Utils::isEmptyLine(configLine))
			continue;
		if (configLine[0] == '#')
			continue;
		configLine = Utils::removeLeadingAndTrailingSpaces(configLine);
		if (configLine == "server {" || Utils::findFirstWord(configLine) == "location")
		{
			throw parseError("block not closed ", this->_lineCount);
			return NULL;
		}
		if (configLine == "}")
			break;
		std::string key = Utils::findFirstWord(configLine);
		// if (key.size() <= 0)
			// throw parseError("not found " + configLine, this->_lineCount);
		newLocation->findKey(key, configLine, this->_lineCount); // removed try/catch block
	}
	newLocation->parameterCheck(this->_lineCount);
	if (this->_configFile.eof())
		throw parseError("end of file ", this->_lineCount);
	return (newLocation);
}

void		ConfigParser::parseTheConfigFile(ServerCluster *serverCluster)
{
	std::string configLine;

	while (std::getline(this->_configFile, configLine))
	{
		++this->_lineCount;
		if (this->_configFile.eof())
			break;
		configLine.erase(std::find(configLine.begin(), configLine.end(), '#'), configLine.end()); // remove comments
		if (Utils::isEmptyLine(configLine))
			continue;
		configLine = Utils::removeLeadingAndTrailingSpaces(configLine);
		if (configLine[0] == '#')
			continue;
		if (configLine != "server {")
			throw parseError("no Server block detected", this->_lineCount);
		Server	*newServer = new Server;
		while (std::getline(this->_configFile, configLine))
		{
			this->_lineCount++;
			if (this->_configFile.eof())
				throw parseError("end of file ", this->_lineCount);
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
			else {
				std::string key = Utils::findFirstWord(configLine);
				// if (key.size() <= 0)
					// throw parseError("not found " + configLine, this->_lineCount);
				newServer->findKey(key, configLine, this->_lineCount); // removed try/catch block
			}
		}
		newServer->setAutoIndexOfLocations();
		newServer->parameterCheck(this->_lineCount);
		serverCluster->addServer(newServer);
		std::cout << *newServer << std::endl;
	}
	if (serverCluster->clusterIsEmpty())
		throw clusterError("Cluster seems to be empty", "check your input");
}

