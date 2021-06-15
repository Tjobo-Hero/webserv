/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 13:54:38 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/15 16:29:18 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ConfigParser.hpp"
#include "Location.hpp"

Server::Server() : _portNumber(0), _maxBodySize(1000000), _autoIndex(false), _errorPage(DEFAULT_ERROR_PAGE), _socketFD(-1) {
	this->_typeFunctionMap.insert(std::make_pair("listen", &Server::setPortNumber));
	this->_typeFunctionMap.insert(std::make_pair("client_max_body_size", &Server::setMaxBodySize));
	this->_typeFunctionMap.insert(std::make_pair("autoindex", &Server::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("root", &Server::setRoot));
	this->_typeFunctionMap.insert(std::make_pair("error_page", &Server::setErrorPage));
	this->_typeFunctionMap.insert(std::make_pair("host", &Server::setHost));
	this->_typeFunctionMap.insert(std::make_pair("server_name", &Server::setServerNames));
	this->_typeFunctionMap.insert(std::make_pair("index", &Server::setIndices));
	return;
}

Server::Server(Server const &src) : _portNumber(), _maxBodySize(), _autoIndex() {
	if (this != &src)
		*this = src;
	return;
}

Server::~Server(void) {
	close(this->_socketFD);
	std::vector<Location*>::iterator it;
	it = this->_locations.begin();
	while (!this->_locations.empty() && it != this->_locations.end())
	{
		delete (*it);
		++it;
	}
	return;
}

Server&			Server::operator=(Server const &obj) {
	if (this != &obj) {
		this->_portNumber = obj._portNumber;
		this->_maxBodySize = obj._maxBodySize;
		this->_autoIndex = obj._autoIndex;
		this->_root = obj._root;
		this->_errorPage = obj._errorPage;
		this->_host = obj._host;
		this->_serverNames = obj._serverNames;
		this->_indices = obj._indices;
		this->_typeFunctionMap = obj._typeFunctionMap;
		this->_locations = obj._locations;
		this->_socketFD = obj._socketFD;
		this->_addr = obj._addr;
	}
	return *this;
}


void			Server::setPortNumber(std::string &listen) {
	std::stringstream ss;
	ss << listen;
	ss >> this->_portNumber;
	return;
}

void 			Server::setMaxBodySize(std::string &maxBodySize) {
	std::stringstream ss;
	ss << maxBodySize;
	ss >> this->_maxBodySize;
	return;
}

void			Server::setAutoIndex(std::string &autoIndex) {
	if (autoIndex == "on")
		this->_autoIndex = true;
	else if (autoIndex == "off")
		this->_autoIndex = false;
	else
		throw parseError(autoIndex, "invalid auto_index");
	return;
}

void			Server::setRoot(std::string &root) {
	this->_root = root;
	return;
}

void			Server::setErrorPage(std::string &errorPage) {
	this->_errorPage = errorPage;
	return;
}

void			Server::setHost(std::string &host) {
	this->_host = host;
	return;
}

void			Server::setServerNames(std::string &serverNames) {
	std::stringstream ss;
	std::string serverName;
	ss << serverNames;
	while (ss >> serverName) {
		this->_serverNames.push_back(serverName);
	}
	return;
}

void			Server::setIndices(std::string &indices) {
	std::stringstream ss(indices);
	std::string index;
	
	while (ss >> index)
		this->_indices.push_back(index);
	return;
}

void			Server::setAlternativeServers(Server *alternative) {
	this->_alternativeServers.push_back(alternative);
	return;
}

const int&		Server::getPortNumber() const {
	return this->_portNumber;
}

const size_t&	Server::getMaxBodySize() const {
	return this->_maxBodySize;
}

const bool&		Server::getAutoIndex() const {
	return this->_autoIndex;
}

const std::string&	Server::getRoot() const {
	return this->_root;
}

const std::string&	Server::getErrorPage() const {
	return this->_errorPage;
}

const std::string&	Server::getHost() const {
	return this->_host;
}

const std::vector<std::string>&	Server::getServerNames() const {
	return this->_serverNames;
}

const std::vector<std::string>&	Server::getIndices() const {
	return this->_indices;
}

const std::vector<Location*>&	Server::getLocations() const {
	return this->_locations;
}

const long&	Server::getSocketFD() const {
	return this->_socketFD;
}

const struct sockaddr_in&	Server::getSocketAddress() const {
	return this->_addr;
}

void		Server::addLocation(Location *newLocation) {
	this->_locations.push_back(newLocation);
	return;
}

void		Server::findKey(std::string &key, std::string configLine, int lineCount)
{
	std::string parameter;
	
	if (*(configLine.rbegin()) != ';')
		throw parseError("HALLO syntax error, line doesn't end with ';' ", lineCount);
	std::map<std::string, setter>::iterator it;

	it = this->_typeFunctionMap.find(key);
	if (it == this->_typeFunctionMap.end())
		throw parseError ("unknown key: " + configLine + " ", lineCount);
	configLine.resize(configLine.size() - 1); //remove the ';'
	parameter = configLine.substr(configLine.find_first_of(WHITESPACE, 0));
	parameter = Utils::removeLeadingAndTrailingSpaces(parameter);
	(this->*(this->_typeFunctionMap.at(key)))(parameter);
	return;
}

bool	Server::parameterCheck(int &lineCount) const {
	if (this->_portNumber <= 0)
		throw parseError("invalid port number ", lineCount);
	if (this->_host.empty())
		throw parseError("invalid host ", lineCount);
	return true;
}

void	Server::setAutoIndexOfLocations()
{
	std::vector<Location*> locs = this->getLocations();
	for (std::vector<Location*>::iterator it = locs.begin(); it != locs.end(); it++)
	{
		if ((*it)->hasOwnAutoIndex() == false)
		{
			if (this->getAutoIndex() == true)
				(*it)->setAutoIndex("on");
			else
				(*it)->setAutoIndex("off");
		}
		if (!(*it)->hasOwnBodySize())
		{
			std::stringstream ss;
			ss << this->getMaxBodySize();
			(*it)->setMaxBodySize(ss.str());
		}
	}
	return;
}

std::ostream&	operator<<(std::ostream &os, const Server &server)
{
	static int serverCount = 1;
	std::vector<std::string> serverNames;
	std::vector<std::string> serverIndices;
	
	serverNames = server.getServerNames();
	serverIndices = server.getIndices();
	std::vector<std::string>::iterator it_server_name = serverNames.begin();
	std::vector<std::string>::iterator it_indices = serverIndices.begin();

	std::cout << std::setfill('.');
	os << "Serverblock: " << serverCount << '\n';
	
	for (;!serverNames.empty() && it_server_name != serverNames.end(); ++it_server_name) {
		os << std::setw(15) << std::left << "server_name:" << *it_server_name << '\n';
	}
	os	<< std::setw(15) << std::left << "port_mumber:" << server.getPortNumber() << '\n'
		<< std::setw(15) << std::left << "host:" << server.getHost() << '\n'
		<< std::setw(15) << "error_page:" << server.getErrorPage() << '\n'
		<< std::setw(15) << std::left << "autoindex:" << ((server.getAutoIndex() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << "root:" << server.getRoot() << '\n';
	for (;!serverIndices.empty() && it_indices != serverIndices.end(); ++it_indices) {
		os << std::setw(15) << std::left << "index" << *it_indices << '\n';
	}
	os	<< std::setw(15) << "socketfd:" << server.getSocketFD() << '\n'
		<< std::setw(15) << "max_body_size:" << server.getMaxBodySize() << '\n'
		<< std::setw(15) << std::setfill(' ') << "locations in this server:" << "\n\n";
	for (size_t i = 0; i < server.getLocations().size(); ++i) {
		os << "locationBlock: " << i + 1 << '\n';
		server.getLocations()[i]->printLocation();
	}
	++serverCount;
	return os;
}