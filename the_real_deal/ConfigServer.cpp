/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:26 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 16:04:39 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"


ConfigServer::ConfigServer(void): _root(""), _clientBodyBufferSize(0), _autoIndex(false), _aliasSet(false)
{
	return ;
}
ConfigServer::~ConfigServer(void)
{
	return;
}

ConfigServer::ConfigServer(ConfigServer const &src) {
	if (this != &src) {
		this->_listen = src._listen;
		this->_root = src._root;
		this->_serverName = src._serverName;
		this->_errorPage = src._errorPage;
		this->_clientBodyBufferSize = src._clientBodyBufferSize;
		this->_cgiParam = src._cgiParam;
		this->_cgiPass = src._cgiPass;
		this->_location = src._location;
		this->_allowedMethods = src._allowedMethods;
		this->_autoIndex = src._autoIndex;
		this->_index = src._index;
		this->_alias = src._alias;
		this->_aliasSet = src._aliasSet;
	}
	return ;
}

ConfigServer	&ConfigServer::operator=(ConfigServer const &src) {
	if (this != &src) {
		this->_listen = src._listen;
		this->_root = src._root;
		this->_serverName = src._serverName;
		this->_errorPage = src._errorPage;
		this->_clientBodyBufferSize = src._clientBodyBufferSize;
		this->_cgiParam = src._cgiParam;
		this->_cgiPass = src._cgiPass;
		this->_location = src._location;
		this->_allowedMethods = src._allowedMethods;
		this->_autoIndex = src._autoIndex;
		this->_index = src._index;
		this->_alias = src._alias;
		this->_aliasSet = src._aliasSet;
	}
	return *this;
}

parseMap ConfigServer::_initServerMap() {
		    parseMap	myMap;
		    myMap["listen"] = &ConfigServer::setListen;
		    myMap["root"] = &ConfigServer::setRoot;
		    myMap["server_name"] = &ConfigServer::setServerName;
		    myMap["error_page"] = &ConfigServer::setErrorPage;
		    myMap["client_body_buffer_size"] = &ConfigServer::setClientBodyBufferSize;
			myMap["cgi_param"] = &ConfigServer::setCgiParam;
			myMap["cgi_pass"] = &ConfigServer::setCgiPass;
			myMap["allow_methods"] = &ConfigServer::setAllowedMethods;
			myMap["index"] = &ConfigServer::setIndex;
			myMap["autoindex"] = &ConfigServer::setAutoIndex;
		    return myMap;
}

parseMap ConfigServer::_initLocationMap() {
			parseMap     myMap;
			myMap["root"] = &ConfigServer::setRoot;
			myMap["error_page"] = &ConfigServer::setErrorPage;
			myMap["client_body_buffer_size"] = &ConfigServer::setClientBodyBufferSize;
			myMap["cgi_param"] = &ConfigServer::setCgiParam;
			myMap["cgi_pass"] = &ConfigServer::setCgiPass;
			myMap["allow_methods"] = &ConfigServer::setAllowedMethods;
			myMap["index"] = &ConfigServer::setIndex;
			myMap["autoindex"] = &ConfigServer::setAutoIndex;
			myMap["alias"] = &ConfigServer::setAlias;
			return myMap;
}

ConfigServer	ConfigServer::_defaultServer = ConfigServer();
parseMap		ConfigServer::locationParsingMap = ConfigServer::_initLocationMap();
parseMap		ConfigServer::serverParsingMap = ConfigServer::_initServerMap();

int		ConfigServer::parseLocation(size_t &index, configVector &file) 
{
	configVector			args;
	parseMap::iterator		iter;
	std::string				directive = "";

	if (file[index++] != "{")
		return 0;
	//	calling the function that corresponds to a directive with its args as parameters
	for ( ; index < file.size() && file[index] != "}" ; index++) {
		if ((iter = ConfigServer::locationParsingMap.find(file[index])) == ConfigServer::locationParsingMap.end()) {
			if (file[index] == "location") {
				ConfigServer	location;
				std::string		locationName;

				if (directive != "") {
					(this->*ConfigServer::locationParsingMap[directive])(args);
					args.clear();
					directive = "";
				}
				index++;
				if (file[index] == "{" || file[index] == "}")
					return 0;
				locationName = file[index];
				index++;
				if (!location.parseLocation(index, file))
					return 0;
				this->_location[locationName] = location;
				if (file[index] == "}")
					continue ;
			}
			else if (directive == "")
				return file[index] == "}" ? 1 : 0;
			else
				args.push_back(file[index]);
		}
		else
		{
			if (directive != "") {
				(this->*ConfigServer::locationParsingMap[directive])(args);
				args.clear();
			}
			directive = iter->first;
		}
	}
	if (directive != "")
		(this->*ConfigServer::locationParsingMap[directive])(args);
	//  set up default values if they were not set by the config file
	if (!file[index].compare("}"))
		return 1;
	return 0;
}

int		ConfigServer::serverParser(size_t &index, configVector &elements)
{
	configVector		args;
	parseMap::iterator	it;
	std::string			directive;
	
	// std::vector<std::string>::const_iterator iter = elements.begin();
	// int i = 0;
	// for(; iter != elements.end(); iter++)
	// {
	// 	std::cout << "index " << i << " : ";
	// 	std::cout << *iter << std::endl;
	// 	i++;
	// }
	
	// std::map<std::string, void (ConfigServer::*)(configVector)>::const_iterator iter = serverParsingMap.begin();
	// int i = 0;
	// for(; iter != serverParsingMap.end(); iter++)
	// {
	// 	std::cout << "index " << i << " : ";
	// 	std::cout << iter->first << std::endl;
	// 	i++;
	// }
	for (; index < elements.size() && elements[index] != "}"; ++index)
	{
		if ((it = ConfigServer::serverParsingMap.find(elements[index])) == ConfigServer::serverParsingMap.end())
		{
			if(elements[index] == "location")
			{
				ConfigServer	location;
				std::string		locationName;
				
				if (directive != "")
				{
					(this->*ConfigServer::serverParsingMap[directive])(args);
					args.clear();
					directive = "";
				}
				index++;
				if (elements[index] == "{" || elements[index] == "}")
					return 0;
				locationName = elements[index];
				index++;
				if (!location.parseLocation(index, elements))
					return 0;
				this->_location[locationName] = location;
				if (elements[index] == "}")
					continue ;
			}
			else if (directive.compare("") == 0) // if directive is empty
				return elements[index] == "}" ? 1 : 0;
			else
				args.push_back(elements[index]);
		}
		else
		{
			if (directive != "")
			{
				(this->*ConfigServer::serverParsingMap[directive])(args);
				args.clear();
			}
			directive = it->first;
		}
	}
	if (directive != "")
		(this->*ConfigServer::serverParsingMap[directive])(args);
	if (elements[index].compare("}") == 0) // the compare it true
	{
		ConfigServer::_defaultServer.passMembers(*this);
		for (std::map<std::string, ConfigServer>::iterator it = this->_location.begin(); it != _location.end(); ++it)
			this->passMembers(it->second);
		return 1;
	}
	return 0;
}

ConfigServer				ConfigServer::_initDefaultServer(const char *filename) {
	ConfigServer	server;
	configVector		file;

	file = ConfigReader::readfile(filename);
	if (file.empty()) {
		std::cerr << "Could not open default file at location [" << filename << "]"  << std::endl;
		throw ConfigReader::NotAValidFileException();
	}
	// configVector	begin;

	// begin.push_back("server");
	// begin.push_back("{");
	// file.insert(file.begin(), begin.begin(), begin.end());
	// file.insert(file.end(), "}");
	size_t	index = 0;
	
	if (!server.serverParser(index, file)) {
		std::cerr << "Invalid default config file." << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	ConfigServer::_defaultServer = server;
	return server;
}

const char		*ConfigServer::ExceptionInvalidArguments::what()
 const throw() {
	return "Exception: invalid arguments in configuration file";
}

void			ConfigServer::setListen(std::vector<std::string> element)
{
	t_listen	listen;
	size_t		separator;

	if (element.size() != 1) // how do we receive a single argument vector?
		throw ConfigServer::ExceptionInvalidArguments();
	if ((separator = element[0].find(":")) == std::string::npos)
	{
		if (isDigitString(element[0]) == true)
		{
			listen.host = 0;
			listen.port = ft_atoi(element[0].c_str());
			for (std::vector<t_listen>::const_iterator it = _listen.begin(); it != _listen.end(); ++it)
			{
				if (it->port == listen.port)
					throw ConfigServer::ExceptionInvalidArguments();
			}
			this->_listen.push_back(listen);
			return;
		}
		throw ConfigServer::ExceptionInvalidArguments();
	}
	else
	{
		listen.host = strToIp(element[0].substr(0, separator));
		separator++;
		std::string portStr = element[0].substr(separator);
		if (isDigitString(portStr))
		{
			listen.port = ft_atoi(portStr.c_str());
			this->_listen.push_back(listen);
			return;
		}
		throw ConfigServer::ExceptionInvalidArguments();
	}
}

void        ConfigServer::setRoot(std::vector<std::string> element) {
	if (element.size() != 1 || this->_root != "")
		throw ConfigServer::ExceptionInvalidArguments();
	this->_root = element[0];
}

void        ConfigServer::setServerName(std::vector<std::string> element) {
	if (element.size() == 0)
		throw ConfigServer::ExceptionInvalidArguments();
	for (unsigned int i = 0; i < element.size(); i++)
		this->_serverName.push_back(element[i]);
}

void        ConfigServer::setClientBodyBufferSize(std::vector<std::string> element) {
	if (element.size() != 1 || !isDigitString(element[0]))
		throw ConfigServer::ExceptionInvalidArguments();
	this->_clientBodyBufferSize = ft_atoi(element[0].c_str());
}

void		ConfigServer::setCgiParam(std::vector<std::string> element) {
	if (element.size() != 2)
		throw ConfigServer::ExceptionInvalidArguments();
	this->_cgiParam[element[0]] = element[1];
}

void    	ConfigServer::setCgiPass(std::vector<std::string> elements) {
	if (elements.size() != 1)
		throw ConfigServer::ExceptionInvalidArguments();
	this->_cgiPass = elements[0];
}

void	ConfigServer::setAutoIndex(std::vector<std::string> element) {
	if (element.size() != 1)
		throw ConfigServer::ExceptionInvalidArguments();
	if (element[0] == "on")
		this->_autoIndex = true;
	else if (element[0] == "off")
		this->_autoIndex = false;
	else
		throw ConfigServer::ExceptionInvalidArguments();
}

void	ConfigServer::setAlias(std::vector<std::string> element) {
	if (element.size() > 1)
		throw ConfigServer::ExceptionInvalidArguments();
	if (element.size())
		this->_alias = element[0];
	this->_aliasSet = true;
}

void	ConfigServer::setAllowedMethods(std::vector<std::string> element)
{
	if (element.empty())
		throw ConfigServer::ExceptionInvalidArguments();
	this->_allowedMethods.clear();
	for (configVector::iterator it = element.begin(); it != element.end(); ++it)
	{
		this->_allowedMethods.insert(*it);
	}
}

void	ConfigServer::setErrorPage(std::vector<std::string> args)
{
	std::vector<int>	codes;
	std::string			uri = "";
	size_t				len = args.size();
	
	for (size_t i = 0; i < len; ++i)
	{
		if (isDigitString(args[i]))
			codes.push_back(ft_atoi(args[i].c_str()));
		else if (codes.empty())
			throw ConfigServer::ExceptionInvalidArguments();
		else if (i == len -1)
			uri = args[i];
		else
			throw ConfigServer::ExceptionInvalidArguments();
	}
	if (uri == "")
		throw ConfigServer::ExceptionInvalidArguments();
	for (std::vector<int>::iterator it = codes.begin(); it != codes.end(); ++it)
	{
		this->_errorPage[*it] = uri;
	}
}