/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 15:10:54 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/09 17:27:11 by rbraaksm      ########   odam.nl         */
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

void	ConfigParser::findServer(std::string key, Server *newServer)
{
	newServer->findKey(key, _it->second, _it->first);
	newServer->addParameter(key, Utils::createParameter(this->_it->second));
}

void	ConfigParser::findLocation(std::string key, Location *newLocation)
{
	int i = 0;
	if (newLocation->foundKey(key, &i) == false)
		throw parseError("key invalid, not found key: " + key + " ", _it->first);
	newLocation->addParameter(Utils::createParameter(this->_it->second), i);
}

void	ConfigParser::createKey(bool server, Server *newServer, Location *newLocation)
{
	std::string key;
	key = Utils::findFirstWord(this->_it->second);
	if (server == true)
		findServer(key, newServer);
	else
		findLocation(key, newLocation);
}



void	ConfigParser::setLocation(Server *newServer)
{
	std::string locationPath = Utils::checkLocationPath(this->_it->second, this->_it->first);
	Location *newLocation = new Location(locationPath);

	++this->_it;
	for (; this->_it->second != "}"; ++this->_it)
	{
		if (this->_it->second == "server {" || Utils::findFirstWord(this->_it->second) == "location")
			throw parseError("location block isn't closed ", this->_it->first);
		createKey(false, NULL, newLocation);
	}
	newLocation->parameterCheck(this->_it->first);
	newServer->addLocation(newLocation);
}

void	ConfigParser::configNewServer(Server *newServer)
{
	newServer->setAutoIndexOfLocations();
	newServer->parameterCheck(this->_it->first);
}

void	ConfigParser::createServer(ServerCluster *serverCluster)
{
	Server	*newServer = new Server;
	++this->_it;
	for (; _it->second != "}"; ++_it)
	{
		if (Utils::findFirstWord(_it->second) == "location")
			this->setLocation(newServer);
		else
			createKey(true, newServer, NULL);
	}
	configNewServer(newServer);
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

void	ConfigParser::getInfoFromConfigFile(void)
{
	Utils::openTextFile(this->_configFile, this->_argv[1]);
	this->_configLines = Utils::getLinesFromTextFile(&this->_configFile);
	Utils::checkBrackets(this->_configLines);
	Utils::deleteSpacesBeforeAndAfter(this->_configLines);
	Utils::checkEndOfLineForSemicolon(this->_configLines);
	Utils::closeTextFile(this->_configFile);
}

void	ConfigParser::parseTheConfigFile(ServerCluster *serverCluster)
{
	getInfoFromConfigFile();
	this->lookingForServer(serverCluster);
	if (serverCluster->clusterIsEmpty())
		throw clusterError("Cluster seems to be empty", "check your input");
	_configLines.clear();
}
