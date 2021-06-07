/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:26 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 09:21:07 by timvancitte   ########   odam.nl         */
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

// const std::vector<std::string> ConfigServer::HTTPMethods = {
// 	"GET",
// 	"HEAD", 
// 	"POST", 
// 	"PUT", 
// 	"DELETE",
// 	"OPTIONS", 
// 	"TRACE", 
// 	"PATCH",
// };

ConfigServer::ConfigServer(ConfigServer const &src) {
	if (this != &src) {
		this->_listen = src._listen;
		this->_root = src._root;
		this->_serverName = src._serverName;
		this->_errorPage = src._errorPage;
		this->_clientBodyBufferSize = src._clientBodyBufferSize;
		this->_cgiParameter = src._cgiParameter;
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
		this->_cgiParameter = src._cgiParameter;
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
			myMap["cgi_param"] = &ConfigServer::setCgiParameter;
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
			myMap["cgi_param"] = &ConfigServer::setCgiParameter;
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

int		ConfigServer::locationBlockParser(size_t &index, configFileVector &configFileElements) 
{
	configFileVector		parameter;
	parseMap::iterator		iter;
	std::string				directive = "";

	if (configFileElements[index++] != "{")
		return 0;
	//	calling the function that corresponds to a directive with its parameter as parameters
	for ( ; index < configFileElements.size() && configFileElements[index] != "}" ; index++) {
		if ((iter = ConfigServer::locationParsingMap.find(configFileElements[index])) == ConfigServer::locationParsingMap.end()) {
			if (configFileElements[index] == "location") {
				ConfigServer	locationBlock;
				std::string		locationName;

				if (directive != "") {
					(this->*ConfigServer::locationParsingMap[directive])(parameter);
					parameter.clear();
					directive = "";
				}
				index++;
				if (configFileElements[index] == "{" || configFileElements[index] == "}")
					return 0;
				locationName = configFileElements[index];
				index++;
				if (!locationBlock.locationBlockParser(index, configFileElements))
					return 0;
				this->_location[locationName] = locationBlock;
				if (configFileElements[index] == "}")
					continue ;
			}
			else if (directive == "")
				return configFileElements[index] == "}" ? 1 : 0;
			else
				parameter.push_back(configFileElements[index]);
		}
		else
		{
			if (directive != "") {
				(this->*ConfigServer::locationParsingMap[directive])(parameter);
				parameter.clear();
			}
			directive = iter->first;
		}
	}
	if (directive != "")
		(this->*ConfigServer::locationParsingMap[directive])(parameter);
	//  set up default values if they were not set by the config file
	if (!configFileElements[index].compare("}"))
		return 1;
	return 0;
}

int		ConfigServer::serverBlockParser(size_t &index, configFileVector &configFileElements)
{
	configFileVector		parameter;
	parseMap::iterator		it;
	std::string				directive;
	
	// std::vector<std::string>::const_iterator iter = configFileElements.begin();
	// int i = 0;
	// for(; iter != configFileElements.end(); iter++)
	// {
	// 	std::cout << "index " << i << " : ";
	// 	std::cout << *iter << std::endl;
	// 	i++;
	// }
	
	// std::map<std::string, void (ConfigServer::*)(configFileVector)>::const_iterator iter = serverParsingMap.begin();
	// int i = 0;
	// for(; iter != serverParsingMap.end(); iter++)
	// {
	// 	std::cout << "index " << i << " : ";
	// 	std::cout << iter->first << std::endl;
	// 	i++;
	// }
	
	for (; index < configFileElements.size() && configFileElements[index] != "}"; ++index)
	{
		if ((it = ConfigServer::serverParsingMap.find(configFileElements[index])) == ConfigServer::serverParsingMap.end())
		{
			std::cout << "IT: " << it->second << std::endl;
			if(configFileElements[index] == "location")
			{
				std::cout << "test\n";
				ConfigServer	locationBlock;
				std::string		locationName;
				
				if (directive != "")
				{
					(this->*ConfigServer::serverParsingMap[directive])(parameter);
					parameter.clear();
					directive = "";
				}
				index++;
				if (configFileElements[index] == "{" || configFileElements[index] == "}")
					return 0;
				locationName = configFileElements[index];
				index++;
				if (!locationBlock.locationBlockParser(index, configFileElements))
					return 0;
				this->_location[locationName] = locationBlock;
				if (configFileElements[index] == "}")
					continue ;
			}
			else if (directive.compare("") == 0) // if directive is empty
			{
				std::cout << "TEST\n";
				return configFileElements[index] == "}" ? 1 : 0;
			}
			else
			{
				parameter.push_back(configFileElements[index]);
			}
		}
		else
		{
			if (directive != "")
			{
				(this->*ConfigServer::serverParsingMap[directive])(parameter);
				parameter.clear();
			}
			directive = it->first;
			std::cout << "Directive:" << directive << std::endl;
		}
	}
	if (directive != "")
		(this->*ConfigServer::serverParsingMap[directive])(parameter);
	if (configFileElements[index].compare("}") == 0) // if this is true
	{
		ConfigServer::_defaultServer.setDefaultDirectiveParametersIfNotSet(*this);
		for (std::map<std::string, ConfigServer>::iterator it = this->_location.begin(); it != _location.end(); ++it)
			this->setDefaultDirectiveParametersIfNotSet(it->second);
		return 1;
	}
	return 0;
}

void	ConfigServer::setDefaultDirectiveParametersIfNotSet(ConfigServer &server) const {
	if (this != &server) {
		if (server._listen.empty())
			server._listen.insert(server._listen.begin(), this->_listen.begin(), this->_listen.end());
		if (server._root == "")
			server._root = this->_root;
		server._serverName.insert(server._serverName.end(), this->_serverName.begin(), this->_serverName.end());
		for (std::map<int, std::string>::const_iterator i = this->_errorPage.begin(); i != this->_errorPage.end(); i++) {
			if (server._errorPage.find(i->first) == server._errorPage.end())
				server._errorPage[i->first] = i->second;
		}
		if (server._clientBodyBufferSize == 0)
			server._clientBodyBufferSize = this->_clientBodyBufferSize;
		for (std::map<std::string, std::string>::const_iterator i = this->_cgiParameter.begin() ; i != this->_cgiParameter.end(); i++) {
			if (server._cgiParameter.find(i->first) == server._cgiParameter.end())
				server._cgiParameter[i->first] = i->second;
		}
		if (server._cgiPass == "")
			server._cgiPass = this->_cgiPass;
		if (server._allowedMethods.empty())
			server._allowedMethods = this->_allowedMethods;
		server._index.insert(server._index.begin(), this->_index.begin(), this->_index.end());
	}
	for (std::map<std::string, ConfigServer>::iterator i = server._location.begin(); i != server._location.end(); i++)
		server.setDefaultDirectiveParametersIfNotSet(i->second);
}
ConfigServer				ConfigServer::_initDefaultServer(const char *filename)
{
	ConfigServer			server;
	configFileVector		configFileElements;

	configFileElements = ConfigFileReader::readConfigFile(filename);
	if (configFileElements.empty()) {
		std::cerr << "Could not open default file at location [" << filename << "]"  << std::endl;
		throw ConfigFileReader::NotAValidFileException();
	}
	// configFileVector	begin;

	// begin.push_back("server");
	// begin.push_back("{");
	// file.insert(file.begin(), begin.begin(), begin.end());
	// file.insert(file.end(), "}");
	size_t	index = 0;
	
	if (!server.serverBlockParser(index, configFileElements)) {
		std::cerr << "Error: ServerBlockParser" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	ConfigServer::_defaultServer = server;
	return server;
}

const char		*ConfigServer::ExceptionInvalidArguments::what()
 const throw() {
	return "Exception: invalid arguments in configuration file";
}

void			ConfigServer::setListen(std::vector<std::string> parameter)
{
	t_listen	listen;
	size_t		separator;

	if (parameter.size() != 1) // how do we receive a single argument vector?
	{
		std::cerr << "Error: setListen Size" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	if ((separator = parameter[0].find(":")) == std::string::npos)
	{
		if (ft::isDigitString(parameter[0]) == true)
		{
			listen.host = 0;
			listen.port = ft::atoi(parameter[0].c_str());
			for (std::vector<t_listen>::const_iterator it = _listen.begin(); it != _listen.end(); ++it)
			{
				if (it->port == listen.port)
				{
					std::cerr << "Error: already existing port" << std::endl;		
					throw ConfigServer::ExceptionInvalidArguments();
				}
			}
			this->_listen.push_back(listen);
			return;
		}
		std::cerr << "Error: setListen undifiend behaviour with seperator" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	else
	{
		listen.host = ft::strToIp(parameter[0].substr(0, separator));
		separator++;
		std::string portStr = parameter[0].substr(separator);
		if (ft::isDigitString(portStr))
		{
			listen.port = ft::atoi(portStr.c_str());
			this->_listen.push_back(listen);
			return;
		}
		std::cerr << "Error: setListen undifiend behaviour without" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
}

void		ConfigServer::setRoot(std::vector<std::string> parameter) {
	if (parameter.size() != 1 || this->_root != "")
	{
		std::cerr << "Error: setRoot" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	this->_root = parameter[0];
}

void		ConfigServer::setServerName(std::vector<std::string> parameter) {
	if (parameter.size() == 0)
	{
		std::cerr << "Error: setServerName" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	for (unsigned int i = 0; i < parameter.size(); i++)
		this->_serverName.push_back(parameter[i]);
}

void		ConfigServer::setClientBodyBufferSize(std::vector<std::string> parameter) {
	if (parameter.size() != 1 || !ft::isDigitString(parameter[0]))
	{
		std::cerr << "Error: setCleintBodyBufferSize" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	
	this->_clientBodyBufferSize = ft::atoi(parameter[0].c_str());
}
void		ConfigServer::setIndex(std::vector<std::string> parameter)
{
	std::cout << "TEST\n";
	if (parameter.empty())
	{
		std::cerr << "Error: setIndex" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	this->_index.insert(this->_index.end(), parameter.begin(), parameter.end());
	std::vector<std::string>::iterator it = this->_index.begin();
	for (; it != this->_index.end(); ++it)
		std::cout << "index: " << *it << std::endl;
}	
void		ConfigServer::setCgiParameter(std::vector<std::string> parameter) {
	if (parameter.size() != 2)
	{
		std::cerr << "Error: setCgiParameter" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	this->_cgiParameter[parameter[0]] = parameter[1];
}

void		ConfigServer::setCgiPass(std::vector<std::string> parameter) {
	if (parameter.size() != 1)
	{
		std::cerr << "Error: setCgiPass" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	this->_cgiPass = parameter[0];
}

void	ConfigServer::setAutoIndex(std::vector<std::string> parameter) {
	if (parameter.size() != 1)
	{
		std::cerr << "Error: setAutoIndex" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	if (parameter[0] == "on")
		this->_autoIndex = true;
	else if (parameter[0] == "off")
		this->_autoIndex = false;
	else
		throw ConfigServer::ExceptionInvalidArguments();
}

void	ConfigServer::setAlias(std::vector<std::string> parameter) {
	if (parameter.size() > 1)
	{
		std::cerr << "Error: setAlias" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	if (parameter.size())
		this->_alias = parameter[0];
	this->_aliasSet = true;
}

void	ConfigServer::setAllowedMethods(std::vector<std::string> parameter)
{
	if (parameter.empty())
	{
		std::cerr << "Error: setAllowedMethods" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	this->_allowedMethods.clear();
	// CHECKEN OF DE ALLOWED METHOD WEL BESTAAT
	for (configFileVector::iterator it = parameter.begin(); it != parameter.end(); ++it)
	{
		this->_allowedMethods.insert(*it);
	}
}

void	ConfigServer::setErrorPage(std::vector<std::string> parameter)
{
	std::vector<int>	error_codes;
	std::string			path_error_uri = "";
	size_t				len = parameter.size();
	
	for (size_t i = 0; i < len; ++i)
	{
		if (ft::isDigitString(parameter[i]))
			error_codes.push_back(ft::atoi(parameter[i].c_str()));
		else if (error_codes.empty())
		{
			std::cerr << "Error: setErrorPage empty" << std::endl;
			throw ConfigServer::ExceptionInvalidArguments();
		}
		else if (i == len -1)
			path_error_uri = parameter[i];
		else
		{	
			std::cerr << "Error: setErroPage undifiend behaviour" << std::endl;	
			throw ConfigServer::ExceptionInvalidArguments();
		}
	}
	if (path_error_uri == "")
	{
		std::cerr << "Error: setErroPage empty path" << std::endl;
		throw ConfigServer::ExceptionInvalidArguments();
	}
	for (std::vector<int>::iterator it = error_codes.begin(); it != error_codes.end(); ++it)
	{
		this->_errorPage[*it] = path_error_uri;
	}
}