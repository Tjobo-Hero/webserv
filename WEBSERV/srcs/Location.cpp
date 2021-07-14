/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/11 10:33:55 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/14 23:03:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "./Parser/ConfigParser.hpp"
#include "Error.hpp"
#include "UsersAndPasswords.hpp"
#include "Utils/Utils.hpp"

Location::Location(void){}

Location::Location(std::string &match) : _autoIndex(false), _ownAutoIndex(false), _ownBodySize(false), _isFileExtension(false), _maxBodySize(1000000)
{
	this->_match = match;
	if (match[0] == '*' && match[1] == '.')
		this->_isFileExtension = true;
	setDirective();
	this->pointerToSetFunction[0] = &Location::setAutoIndex;
	this->pointerToSetFunction[1] = &Location::setMaxBodySize;
	this->pointerToSetFunction[2] = &Location::setHTPasswordPath;
	this->pointerToSetFunction[3] = &Location::setAuthBasic;
	this->pointerToSetFunction[4] = &Location::setCgiPath;
	this->pointerToSetFunction[5] = &Location::setIndices;
	this->pointerToSetFunction[6] = &Location::setErrorPage;
	this->pointerToSetFunction[7] = &Location::setMethod;
	this->pointerToSetFunction[8] = &Location::setRoot;
	return;
}

Location::Location(Location const &src)
{
	if (this != &src)
		*this = src;
	return;
}

Location::~Location(void) {}

Location&	Location::operator=(Location const &obj)
{
	if (this != &obj)
	{
		this->_autoIndex = obj._autoIndex;
		this->_match = obj._match;
		this->_root = obj._root;
		this->_methods = obj._methods;
		this->_errorPage = obj._errorPage;
		this->_indices = obj._indices;
		this->_authBasic = obj._authBasic;
		this->_authBasicUserFile = obj._authBasicUserFile;
		this->_cgiPath = obj._cgiPath;
		this->_isFileExtension = obj._isFileExtension;
		this->_directive = obj._directive;
	}
	return *this;
}

void	Location::setDirective(void)
{
	this->_directive.push_back("autoindex");
	this->_directive.push_back("client_max_body_size");
	this->_directive.push_back("auth_basic_user_file");
	this->_directive.push_back("auth_basic");
	this->_directive.push_back("cgi_exec");
	this->_directive.push_back("index");
	this->_directive.push_back("error_page");
	this->_directive.push_back("method");
	this->_directive.push_back("root");
}

void	Location::printLocation() const
{
	std::cout << *this << std::endl;
}

void	Location::setAutoIndex(const std::string &autoIndex)
{
	this->_ownAutoIndex = true;
	if (autoIndex == "on")
	{
		this->_autoIndex = true;
		return;
	}
}

void	Location::setMaxBodySize(const std::string &maxBodySize)
{
	this->_ownBodySize = true;
	std::stringstream ss;

	ss << maxBodySize;
	ss >> this->_maxBodySize;
	if (this->_maxBodySize == 0)
		this->_maxBodySize = (ULONG_MAX);
}

void	Location::setRoot(const std::string &root)
{
	this->_root = root;
}

void	Location::setMethod(const std::string &method)
{
	std::stringstream ss;
	std::string	methods;

	ss << method;
	while (ss >> methods)
		this->_methods.push_back(methods);
}

void	Location::setErrorPage(const std::string &errorPage)
{
	this->_errorPage = errorPage;
}

void	Location::setIndices(const std::string &indices)
{
	std::stringstream ss;
	std::string	index;

	ss << indices;
	while (ss >> index)
		this->_indices.push_back(index);
}

void	Location::setCgiPath(const std::string &cgiPath)
{
	this->_cgiPath = cgiPath;
}

void	Location::setAuthBasic(const std::string &authBasic)
{
	this->_authBasic = authBasic;
}

void	Location::openUserAndPasswordFile(std::fstream *configFile)
{
	(*configFile).open(this->_htpasswd_path.c_str());
	if (!*configFile)
		throw openFileError("Error: failed to open filepath: ", this->_htpasswd_path);
}

void	Location::setHtpPath(const std::string passwordpath)
{
	this->_htpasswd_path = passwordpath;
}

std::vector<std::string>	Location::getLinesFromFile(std::fstream *configFile)
{
	std::vector<std::string> ret;
	std::string	income;

	while (std::getline(*configFile, income))
		ret.push_back(income);
	(*configFile).close();
	return ret;

}

void	Location::setLogInfo(const UsersAndPasswords &password)
{
	std::map<std::string, std::string> data = password.getUsersAndPasswords();
	std::map<std::string, std::string>::iterator it = data.begin();
	for(; it != data.end(); ++it)
		this->_loginfo[it->first] = it->second;
}

void	Location::setHTPasswordPath(const std::string &passwordpath)
{
	struct stat statstruct = {};

	std::fstream configFile;
	std::vector<std::string> lines;

	if (stat(passwordpath.c_str(), &statstruct) == -1)
		throw parseError("set password path error", "check input");
	setHtpPath(passwordpath);
	openUserAndPasswordFile(&configFile);
	lines = getLinesFromFile(&configFile);
	UsersAndPasswords A;
	A.findUsersAndPasswords(lines);
	setLogInfo(A);
}

const bool&	Location::hasOwnAutoIndex() const
{
	return this->_ownAutoIndex;
}

const bool&	Location::hasOwnBodySize() const
{
	return this->_ownBodySize;
}

const bool&	Location::getAutoIndex() const
{
	return this->_autoIndex;
}

const size_t&	Location::getMaxBodySize() const
{
	return this->_maxBodySize;
}

const std::string&	Location::getHTPasswordPath() const
{
	return this->_htpasswd_path;
}

const std::string&	Location::getMatch() const
{
	return this->_match;
}

const std::string&	Location::getRoot() const
{
	return this->_root;
}

const std::string&	Location::getErrorPage() const
{
	return this->_errorPage;
}

const std::vector<std::string>&	Location::getIndices() const
{
	return this->_indices;
}

const std::vector<std::string>&	Location::getMethods() const
{
	return this->_methods;
}

const std::string&	Location::getCGIPath() const
{
	return this->_cgiPath;
}

const std::string&	Location::getAuthBasic() const
{
	return this->_authBasic;
}

const std::string&	Location::getAuthUserFile() const
{
	return this->_authBasicUserFile;
}

const bool&		Location::getIsFileExtension() const
{
	return this->_isFileExtension;
}

const std::map<std::string, std::string>&	Location::getLogInfo() const
{
	return this->_loginfo;
}

bool	Location::foundKey(std::string key, int *i)
{
	std::vector<std::string>::iterator it = _directive.begin();
	for (; it != _directive.end(); ++it)
	{
		if (*it == key)
			return true;
		++(*i);
	}
	return false;
}

void	Location::findKey(std::string &key, std::string configLine, int lineCount)
{
	if (*(configLine.rbegin()) != ';')
		throw parseError("syntax error, line doesn't end with ';' ", lineCount);

	// std::map<std::string, setter>::iterator it;
	// if ((it = this->directive.find(key)) == this->directive.end())
	int i = 0;
	if (foundKey(key, &i) == false)
		throw parseError("key invalid, not found key: " + key + " ", lineCount);
	std::string parameter;
	parameter = Utils::createParameter(configLine);
	(this->*pointerToSetFunction[i])(parameter);
	// (this->*(this->directive.at(key)))(parameter);
}

bool	Location::checkAllowedMethods(const std::string method) const
{
	for (int i = 0; i < 5; ++i)
		if (method == allowedMethods[i])
			return true;
	return false;
}

bool	Location::parameterCheck(int &lineCount) const
{
	for (std::vector<std::string>::const_iterator it = this->_methods.begin(); it != this->_methods.end(); ++it)
		if (checkAllowedMethods(*it) == false)
			throw parseError("invalid method ", lineCount);
	// if (this->_root.empty() == true)
	// 	throw parseError("missing root ", lineCount);
	return true;
}

bool Location::getAuthMatch(const std::string& username, const std::string& password)
{
	std::map<std::string, std::string>::iterator it = this->_loginfo.find(username);

	if (it == this->_loginfo.end())
		return (false);
	if (password != it->second)
		return (false);
	return (true);
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
	os	<< std::setw(15) << std::left << "location:" << location.getMatch() << '\n'
		<< std::setw(15) << "method:";
	for (;!locationMethods.empty() && it_location_methods != locationMethods.end(); ++it_location_methods)
	{
		os << *it_location_methods;
	}
	os	<< '\n'
		<< std::setw(15) << std::left << "root:" << location.getRoot() << '\n'
		<< std::setw(15) << std::left << "index:";
	for (;!locationIndices.empty() && it_location_indices!= locationIndices.end(); ++it_location_indices)
	{
		os << *it_location_indices;
	}
	os	<< '\n'
		<< std::setw(15) << std::left << "auth_basic:" << location.getAuthBasic() << '\n'
		<< std::setw(15) << std::left << "auth_basic_user_file:" << location.getHTPasswordPath() << '\n'
		<< std::setw(15) << std::left << "client_max_body_size:" << location.getMaxBodySize() << '\n'
		<< std::setw(15) << std::left << "cgi_exec:" << location.getCGIPath() << '\n'
		<< std::setw(15) << std::left << "autoindex:" << ((location.getAutoIndex() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << std::left << "file_extension:" << ((location.getIsFileExtension() == true) ? ("on\n") : ("off\n"))
		<< std::setw(15) << std::left << "error_page:" << location.getErrorPage() << '\n'
		<< std::setw(15) << std::setfill(' ') << "Log info:" << '\n';
	for (; !locationLogInfo.empty() && it_location_loginfo != locationLogInfo.end(); ++it_location_loginfo)
	{
		os << "User:" << it_location_loginfo->first << "Password:" << it_location_loginfo->second << '\n';
	}
	os << "----------------------------------\n";
	return os;
}
