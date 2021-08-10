/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 13:54:38 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/10 10:42:27 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "./Parser/ConfigParser.hpp"
#include "Location.hpp"
#include "./Utils/Utils.hpp"
#include "Response.hpp"

Server::Server(void) : _portNumber(0), _maxBodySize(1000000), _autoIndex(false), _errorPage(DEFAULT_ERROR_PAGE), _socketFD(-1)
{
	this->_typeFunctionMap.insert(std::make_pair("listen", &Server::setPortNumber));
	this->_typeFunctionMap.insert(std::make_pair("client_max_body_size", &Server::setMaxBodySize));
	this->_typeFunctionMap.insert(std::make_pair("autoindex", &Server::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("root", &Server::setRoot));
	this->_typeFunctionMap.insert(std::make_pair("error_page", &Server::setErrorPage));
	this->_typeFunctionMap.insert(std::make_pair("host", &Server::setHost));
	this->_typeFunctionMap.insert(std::make_pair("server_name", &Server::setServerNames));
	this->_typeFunctionMap.insert(std::make_pair("index", &Server::setIndices));
}

Server::Server(Server const &src) : _portNumber(), _maxBodySize(), _autoIndex()
{
	if (this != &src)
		*this = src;
}

Server::~Server(void)
{
	close(this->_socketFD);
	std::vector<Location*>::iterator it;
	it = this->_locations.begin();
	while (!this->_locations.empty() && it != this->_locations.end())
	{
		delete (*it);
		++it;
	}
}

Server&		Server::operator=(Server const &obj)
{
	if (this != &obj)
	{
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

void	Server::setPortNumber(std::string &listen)
{
	std::stringstream ss;
	ss << listen;
	ss >> this->_portNumber;
}

void 	Server::setMaxBodySize(std::string &maxBodySize)
{
	std::stringstream ss;
	ss << maxBodySize;
	ss >> this->_maxBodySize;
}

void	Server::setAutoIndex(std::string &autoIndex)
{
	if (autoIndex == "on")
		this->_autoIndex = true;
	else if (autoIndex == "off")
		this->_autoIndex = false;
	else
		throw parseError(autoIndex, "invalid auto_index");
}

void	Server::setRoot(std::string &root)
{
	this->_root = root;
}

void	Server::setErrorPage(std::string &errorPage)
{
	this->_errorPage = errorPage;
}

void	Server::setHost(std::string &host)
{
	this->_host = host;
}

void	Server::setServerNames(std::string &serverNames)
{
	std::stringstream ss;
	std::string serverName;
	ss << serverNames;
	while (ss >> serverName)
		this->_serverNames.push_back(serverName);
}

void	Server::setIndices(std::string &indices)
{
	std::stringstream ss(indices);
	std::string index;

	while (ss >> index)
		this->_indices.push_back(index);
}

void	Server::setAlternativeServers(Server *alternative)
{
	this->_alternativeServers.push_back(alternative);
}

const int&		Server::getPortNumber() const
{
	return this->_portNumber;
}

const size_t&	Server::getMaxBodySize() const
{
	return this->_maxBodySize;
}

const bool&		Server::getAutoIndex() const
{
	return this->_autoIndex;
}

const std::string&	Server::getRoot() const
{
	return this->_root;
}

const std::string&	Server::getErrorPage() const
{
	return this->_errorPage;
}

const std::string&	Server::getHost() const
{
	return this->_host;
}

const std::vector<std::string>&	Server::getServerNames() const
{
	return this->_serverNames;
}

const std::vector<std::string>&	Server::getIndices() const
{
	return this->_indices;
}

const std::vector<Location*>&	Server::getLocations() const
{
	return this->_locations;
}

const long&	Server::getSocketFD() const
{
	return this->_socketFD;
}

const struct sockaddr_in&	Server::getSocketAddress() const
{
	return this->_addr;
}

void	Server::addLocation(Location *newLocation)
{
	this->_locations.push_back(newLocation);
}

void	Server::addParameter(std::string &key, std::string parameter)
{
	(this->*(this->_typeFunctionMap.at(key)))(parameter);
}

void	Server::findKey(std::string &key, std::string configLine, int lineCount)
{
	std::map<std::string, setter>::iterator it;
	if ((it = this->_typeFunctionMap.find(key)) == this->_typeFunctionMap.end())
		throw parseError ("unknown key: " + configLine + " ", lineCount);
}

bool	Server::parameterCheck(int lineCount) const
{
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
}

Location*	Server::findLocation(std::string &match)
{
	std::vector<Location*>::iterator it;
	for (it = this->_locations.begin(); !this->_locations.empty() && it != this->_locations.end(); ++it)
	{
		if ((*it)->getMatch() == match)
			return (*it);
	}
	return NULL;
}

void	Server::setServer()
{
	Utils::createSocket(this->_socketFD, this->_host);
	Utils::setDataStructureToZero(this->_addr, this->_portNumber);
	Utils::setSocketOption(this->_socketFD, this->_host);
	Utils::bindSocket(this->_socketFD, this->_addr, this->_host);
	Utils::listenSocket(this->_socketFD, this->_host);
	std::cout << "Server startup is succesfull" << std::endl;
}

int		Server::acceptConnections()
{
	struct sockaddr connectingAddr;
	socklen_t		addressLength;
	int				i;

	for (i = 0; i < NR_OF_CONNECTIONS; i++)
	{
		if (this->connections[i].getAcceptFD() == -1)
			break;
	}
	if (i == NR_OF_CONNECTIONS)
		return (0);
	this->connections[i].setFD(accept(this->_socketFD, &connectingAddr, &addressLength));
	if (this->connections[i].getAcceptFD() == -1)
		std::cerr << "Could not create FD" << std::endl;
	this->connections[i].setTimeLastRead(Utils::getTime());
	return (1);
}

static size_t requestNumber = 0;

void	Server::createResponse(int index)
{

	Connection	*currentConnection = &this->connections[index];
	std::cout << " Handling request nr" << requestNumber << std::endl;

#if PRINTLOG == 1

	if (requestNumber >= MAXLOGS)
	{
		std::stringstream oldName;
		oldName << "logs/request_";
		size_t oldNumber = requestNumber - MAXLOGS;
		oldName << oldNumber;
		remove(oldName.str().c_str());
	}
	std::stringstream logName;
	logName << "logs/request_";
	logName << requestNumber;
	std::ofstream reqLog(logName.str().c_str(), std::ios::out);
	reqLog << connections[index].getBuffer();
	reqLog.close();
#endif

#if PRINTOUT == 1
	std::cout << "==REQUEST==" << std::endl;
	int len = std::min(connections[index].getBuffer().length(), (size_t)500);
	if (write(1, connections[index].getBuffer().c_str(), len) == -1)
	{;}
	std::cout << "==end==" << std::endl;

#endif

	Request request(this->connections[index].getBuffer());
	if (!(*this)._alternativeServers.empty())
	{
		if ((*this)._serverNames[0] != request.getHost())
		{
			std::vector<Server*>::const_iterator it;
			for (it = (*this)._alternativeServers.begin(); it != (*this)._alternativeServers.end(); ++it)
			{
				if ((*it)->_serverNames[0] == request.getHost())
				{
					*this = *(*it);
					break;
				}
			}
		}
	}
	currentConnection->myResponse = new Response(request, *this);
	currentConnection->myResponse->setupResponse(request, *this);

	requestNumber += 1;
}

void	Server::setupResponseString(int index)
{
	Connection *currentConnection = &this->connections[index];

	if (!currentConnection->myResponse->isResponseFinished())
	{
		if (currentConnection->myResponse->getUseCGI())
			currentConnection->myResponse->getCGI().executeCGI(currentConnection->myResponse->getBody());
		if (currentConnection->myResponse->getStatus() > 299)
			currentConnection->myResponse->finishErrorPage(*this);
		else if (currentConnection->myResponse->methodType() == "GET")
			currentConnection->myResponse->getMethod();
		else if (currentConnection->myResponse->methodType() == "HEAD")
			currentConnection->myResponse->headMethod();
		else if (currentConnection->myResponse->methodType() == "POST")
			currentConnection->myResponse->finishPost();
		else if (currentConnection->myResponse->methodType() == "PUT")
			currentConnection->myResponse->finishPut();
	}
	this->_bodylen = currentConnection->myResponse->getBodySize();
	currentConnection->setResponseString(currentConnection->myResponse->getResponse());

#if PRINTLOG == 1
	if (requestNumber >= MAXLOGS)
	{
		std::stringstream oldname;
		oldname << "logs/response_";
		size_t oldnr = requestNumber - MAXLOGS;
		oldname << oldnr;
		remove(oldname.str().c_str());
	}
	std::stringstream logname1;
	logname1 << "logs/response_";
	logname1 << requestNumber;
	std::ofstream respLog(logname1.str().c_str(), std::ios::out);
	respLog << currentConnection->getResponseString();
	respLog.close();
#endif
#if PRINTOUT == 1
	std::cout << "==RESPONSE==" << std::endl;
	int len1 = std::min(currentConnection->getResponseString().length(), (size_t)500);
	if (write(1, currentConnection->getResponseString().c_str(), len1) == -1)
	{;}
	std::cout << "\n==end==" << std::endl;
#endif
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

	for (;!serverNames.empty() && it_server_name != serverNames.end(); ++it_server_name)
	{
		os << std::setw(15) << std::left << "server_name:" << *it_server_name << '\n';
	}
	os	<< std::setw(15) << std::left << "port_mumber:" << server.getPortNumber() << '\n'
		<< std::setw(15) << std::left << "host:" << server.getHost() << '\n'
		<< std::setw(15) << "error_page:" << server.getErrorPage() << '\n'
		<< std::setw(15) << std::left << "autoindex:" << ((server.getAutoIndex() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << "root:" << server.getRoot() << '\n';
	for (;!serverIndices.empty() && it_indices != serverIndices.end(); ++it_indices)
	{
		os << std::setw(15) << std::left << "index" << *it_indices << '\n';
	}
	os	<< std::setw(15) << "socketfd:" << server.getSocketFD() << '\n'
		<< std::setw(15) << "max_body_size:" << server.getMaxBodySize() << '\n'
		<< std::setw(15) << std::setfill(' ') << "locations in this server:" << "\n\n";
	for (size_t i = 0; i < server.getLocations().size(); ++i)
	{
		os << "locationBlock: " << i + 1 << '\n';
		server.getLocations()[i]->printLocation();
	}
	++serverCount;
	return os;
}

int		Server::getAlternative()
{
	return _portNumber;
}

void	Server::printAlternativeServers()
{
	std::cout << "Alternative\n";
	std::vector<Server*>::iterator it = _alternativeServers.begin();
	for (; it != _alternativeServers.end(); ++it)
		std::cout << "Alternative server: " << (*it)->getAlternative() << std::endl;
	std::cout << std::endl;
}