/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/11 10:33:55 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/15 10:50:42 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "ConfigParser.hpp"

Location::Location(std::string &match) : _autoIndex(false), _ownAutoIndex(false), _ownBodySize(false), _isFileExtension(false), _maxBodySize(1000000)
{
	this->_match = match;
	if (match[0] == '*' && match[1] == '.')
		this->_isFileExtension = true;
	this->_typeFunctionMap.insert(std::make_pair("autoindex", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("root", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("method", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("error_page", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("index", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("cgi_exec", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("auth_basic", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("auth_basic_user_file", &Location::setAutoIndex));
	this->_typeFunctionMap.insert(std::make_pair("client_max_body_size", &Location::setAutoIndex));
	return;
}

Location::Location(Location const &src) {
	if (this != &src)
		*this = src;
	return;
}

Location::~Location(void) {
	return;
}

Location&	Location::operator=(Location const &obj)
{
	if (this != &obj) {
		this->_autoIndex = obj._autoIndex;
		this->_match = obj._match;
		this->_root = obj._root;
		this->_methods = obj._methods;
		this->_errorPage = obj._errorPage;
		this->_indices = obj._indices;
		this->_typeFunctionMap = obj._typeFunctionMap;
		this->_authBasic = obj._authBasic;
		this->_authBasicUserFile = obj._authBasicUserFile;
		this->_cgiPath = obj._cgiPath;
		this->_isFileExtension = obj._isFileExtension;
	}
	return *this;
}

void		Location::setAutoIndex(const std::string &autoIndex)
{
	this->_ownAutoIndex = true;
	if (autoIndex.compare("on") == true)
	{
		this->_autoIndex = true;
		return;
	}
	if (autoIndex != "off")
	{;}
	// return;
}

void		Location::setMaxBodySize(const std::string &maxBodySize)
{
	this->_ownBodySize = true;

	std::stringstream ss;

	ss << maxBodySize;
	ss >> this->_maxBodySize;
	if (this->_maxBodySize == 0)
		this->_maxBodySize = (ULONG_MAX);
	return;
}

void		Location::setRoot(const std::string &root) {
	this->_root = root;
	return;
}

void		Location::setMethod(const std::string &method) {
	std::stringstream ss;
	std::string	methods;
	
	ss << method;
	while (ss >> methods)
		this->_methods.push_back(methods);
	return;
}

void		Location::setErrorPage(const std::string &errorPage) {
	this->_errorPage = errorPage;
	return;
}

void		Location::setIndices(const std::string &indices) {
	std::stringstream ss;
	std::string	index;

	ss << indices;
	while (ss >> index)
		this->_indices.push_back(index);
	return;
}

void		Location::setCgiPath(const std::string &cgiPath) {
	this->_cgiPath = cgiPath;
	return;
}

void		Location::setAuthBasic(const std::string &authBasic)
{
	this->_authBasic = authBasic;
	return;
}

void		Location::setHTPasswordPath(const std::string &passwordpath)
{
	struct stat statstruct = {};
	if (stat(passwordpath.c_str(), &statstruct) == -1)
	{
		// TODO: Error?
		return;
	}
	this->_htpasswd_path = passwordpath;
	
	std::fstream configFile;
	std::string line;

	configFile.open(this->_htpasswd_path.c_str());
	if (!configFile)
	{
		// TODO error?
		return;
	}
	while (std::getline(configFile, line))
	{
		std::string user;
		std::string pass;
		Utils::getKeyValue(line, user, pass, ":", "\n\r#;");
		this->_loginfo[user] = pass;
	}
	configFile.close();
}


const bool&	Location::hasOwnAutoIndex() const
{
	return this->_ownAutoIndex;
}

const bool&	Location::hasOwnBodySize() const
{
	return this->_ownBodySize;
}

const bool&	Location::getAutoIndex() const {
	return this->_autoIndex;
}

const size_t&	Location::getMaxBodySize() const {
	return this->_maxBodySize;
}

const std::string&	Location::getHTPasswordPath() const {
	return this->_htpasswd_path;
}

const std::string&	Location::getMatch() const {
	return this->_match;
}

const std::string&	Location::getRoot() const {
	return this->_root;
}

const std::string&	Location::getErrorPage() const {
	return this->_errorPage;
}

const std::vector<std::string>&	Location::getIndices() const {
	return this->_indices;
}

const std::vector<std::string>&	Location::getMethods() const {
	return this->_methods;
}

const std::string&	Location::getCGIPath() const {
	return this->_cgiPath;
}

const std::string&	Location::getAuthBasic() const {
	return this->_authBasic;
}

const std::string&	Location::getAuthUserFile() const {
	return this->_authBasicUserFile;
}

const bool&		Location::getIsFileExtension() const {
	return this->_isFileExtension;
}

const std::map<std::string, std::string>&	Location::getLogInfo() const {
	return this->_loginfo;
}
void				Location::findKey(std::string &key, std::string configLine, int lineCount) {
	std::map<std::string, setter>::iterator it;

	std::string parameter;

	if (*(configLine.rbegin()) != ';')
	{
		throw parseError("syntax error, line doesn't end with ';'", lineCount);
		return;
	}
	it = this->_typeFunctionMap.find(key);
	if (it == this->_typeFunctionMap.end())
	{
		throw parseError("key invalid, not found key:" + key, lineCount);
		return;
	}
	configLine.resize(configLine.size() - 1); // remove ';'
	parameter = configLine.substr(configLine.find_first_of(WHITESPACE) + 1);
	(this->*(this->_typeFunctionMap.at(key)))(parameter);
	return;
}

// TODO: deze functie kan echt veel mooier
bool			Location::parameterCheck() const {
	std::vector<std::string>::const_iterator it;
	
	bool ret = true;

	for (it = this->_methods.begin(); it != this->_methods.end(); ++it)
	{
		if ((*it) != allowedMethods[0] && (*it) != allowedMethods[1] && (*it) != allowedMethods[2] && (*it) != allowedMethods[3] && (*it) != allowedMethods[4])
			ret = false;
	}
	if (!ret)
		return (ret);
	return true;	
}

std::ostream&	operator<<(std::ostream &os, const Location &location)
{
	std::vector<std::string> locationMethods;
	std::vector<std::string> locationIndices;
	std::map<std::string, std::string> locationLogInfo;
	locationMethods = location.getMethods();
	locationIndices = location.getIndices();
	locationLogInfo = location.getLogInfo();
	std::vector<std::string>::iterator it_location_methods = locationMethods.begin();
	std::vector<std::string>::iterator it_location_indices = locationIndices.begin();
	std::map<std::string, std::string>::iterator it_location_loginfo = locationLogInfo.begin();


	std::cout << std::setfill('.') << std::left;
	os	<< std::setw(15) << std::left << "match:" << location.getMatch() << '\n'
		<< std::setw(15) << "method:";
	for (;!locationMethods.empty() && it_location_methods != locationMethods.end(); ++it_location_methods) {
		os << *it_location_methods;
	}
	os	<< '\n'
		<< std::setw(15) << std::left << "root:" << location.getRoot() << '\n'
		<< std::setw(15) << std::left << "index:";
	for (;!locationIndices.empty() && it_location_indices!= locationIndices.end(); ++it_location_indices) {
		os << *it_location_indices;
	}
	os	<< '\n'
		<< std::setw(15) << std::left << "auth_basic:" << location.getAuthBasic() << '\n'
		<< std::setw(15) << std::left << "auth_basic_user_file:" << location.getAuthBasic() << '\n'
		<< std::setw(15) << std::left << "client_max_body_size:" << location.getMaxBodySize() << '\n'
		<< std::setw(15) << std::left << "cgi_exec:" << location.getCGIPath() << '\n'
		<< "----------------------------------\n"
		<< std::setw(15) << std::left << "autoindex:" << ((location.getAutoIndex() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << std::left << "file_extension:" << ((location.getIsFileExtension() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << std::left << "error_page:" << location.getErrorPage() << '\n'
		<< std::setw(15) << std::left << "http_password_path:" << location.getHTPasswordPath() << '\n'
		<< std::setw(15) << std::left << "http_password_path:" << location.getHTPasswordPath() << '\n'
		<< std::setw(15) << std::setfill(' ') << "Log info:" << '\n';
	for (; !locationLogInfo.empty() && it_location_loginfo != locationLogInfo.end(); ++it_location_loginfo)
	{
		os << "User:" << it_location_loginfo->first << "Password:" << it_location_loginfo->second << '\n';
	}
	return os;
}