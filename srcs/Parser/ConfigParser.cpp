/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 15:10:54 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/06 16:38:35 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/Utils.hpp"
#include "ConfigParser.hpp"

ConfigParser::ConfigParser(char **argv) : _argv(argv)
{
	return;
}

ConfigParser::ConfigParser(ConfigParser const &src)
{
	if (this != &src)
		*this = src;
	return;
}

ConfigParser::~ConfigParser()
{
	return;
}

ConfigParser&	ConfigParser::operator=(ConfigParser const &obj)
{
	if (this != &obj)
		this->_argv = obj._argv;
	return *this;
}

void	ConfigParser::setLocation(Server *newServer)
{
	std::string locationPath = Utils::checkLocationPath(this->_it->second, this->_it->first);
	Location *newLocation = new Location(locationPath);

	++this->_it;
	while (this->_it->second != "}")
	{
		if (this->_it->second == "server {" || Utils::findFirstWord(this->_it->second) == "location")
			throw parseError("location block isn't closed ", this->_it->first);

		std::string key = Utils::findFirstWord(this->_it->second);
		newLocation->findKey(key, this->_it->second, this->_it->first);
		++this->_it;
	}
	++this->_it;
	newLocation->parameterCheck(this->_it->first);
	newServer->addLocation(newLocation);
}

void	ConfigParser::createServer(ServerCluster *serverCluster)
{
	Server	*newServer = new Server;
	++this->_it;
	while(_it->second != "}")
	{
		if (Utils::findFirstWord(_it->second) == "location")
			this->setLocation(newServer);
		else
		{
			std::string key = Utils::findFirstWord(this->_it->second);
			newServer->findKey(key, this->_it->second, this->_it->first);
			++this->_it;
		}
	}
	newServer->setAutoIndexOfLocations();
	newServer->parameterCheck(this->_it->first);
	serverCluster->addServer(newServer);
	// std::cout << *newServer << std::endl;
}

void	ConfigParser::lookingForServer(ServerCluster *serverCluster)
{
	this->_it = this->_configLines.begin();
	for(; this->_it != this->_configLines.end(); ++this->_it)
	{
		if (this->_it->second != "server {")
			throw parseError("no Server block detected", this->_it->first);
		this->createServer(serverCluster);
	}
}

void	ConfigParser::parseTheConfigFile(ServerCluster *serverCluster)
{
	Utils::openTextFile(this->_configFile, this->_argv[1]);
	this->_configLines = Utils::getLinesFromTextFile(&this->_configFile);
	Utils::deleteEmptyLines(this->_configLines);
	Utils::deleteSpacesBeforeAndAfter(this->_configLines);
	Utils::checkBrackets(this->_configLines);
	Utils::closeTextFile(this->_configFile);
	this->lookingForServer(serverCluster);
	if (serverCluster->clusterIsEmpty())
		throw clusterError("Cluster seems to be empty", "check your input");
	_configLines.clear();
}
