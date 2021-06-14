/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 13:54:38 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/14 12:00:55 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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


void			Server::setPortNumber(const std::string &listen) {
	std::stringstream ss;
	ss << listen;
	ss >> this->_portNumber;
	return;
}

void 			Server::setMaxBodySize(const std::string &maxBodySize) {
	std::stringstream ss;
	ss << maxBodySize;
	ss >> this->_maxBodySize;
	return;
}

void			Server::setAutoIndex(const std::string &autoIndex) {
	if (autoIndex.compare("on"))
		this->_autoIndex = true;
	else if (autoIndex.compare("off"))
		this->_autoIndex = false;
	else
		throw parseError(autoIndex, "invalid auto_index");
	return;
}

void			Server::setRoot(const std::string &root) {
	this->_root = root;
	return;
}

void			Server::setErrorPage(const std::string &errorPage) {
	this->_errorPage = errorPage;
	return;
}

void			Server::setHost(const std::string &host) {
	this->_host = host;
	return;
}

void			Server::setServerNames(const std::string &serverNames) {
	std::stringstream ss;
	std::string serverName;
	ss << serverNames;
	while (ss >> serverName) {
		this->_serverNames.push_back(serverName);
	}
	return;
}

void			Server::setIndices(const std::string &indices) {
	std::stringstream ss;
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

void		Server::findKey(std::string &key, std::string configLine)
{
	std::string parameter;
	
	if (*(configLine.rbegin()) != ';')
	{
		throw parseError("syntax error, line doesn't end with ';'", ConfigParser::getLineCount());
		return;
	}
	std::map<std::string, setter>::iterator it;

	it = this->_typeFunctionMap.find(key);
	if (it == this->_typeFunctionMap.end())
	{
		throw parseError (configLine += ": unknown key", ConfigParser::getLineCount());
		return;
	}
	configLine.resize(configLine.size() - 1); //remove the ';'
	parameter = configLine.substr(configLine.find_first_of(WHITESPACE, 0));
	(this->*(this->_typeFunctionMap.at(key)))(parameter);
	return;
}

bool	Server::parameterCheck() const {
	if (this->_portNumber <= 0)
		return false;
	if (this->_host.empty())
		return false;
	return true;
}