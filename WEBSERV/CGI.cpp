/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:12:22 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/23 14:49:40 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"
#include "ConnectionUtils.hpp"
#include "Error.hpp"

CGI::CGI(std::string &path, Request &request, Server &server) :
	_path(path),
	_type(request.getFileType()) {
		_initEnvironment(request, server);
	}

CGI::CGI() {}

CGI::CGI(CGI &src) {
	if (this != &src) {
		this->_environment = src._environment;
	}
	return ;
}

CGI::~CGI() {
	_environment.clear();
}

void	CGI::setupIn() {
	if ((this->_fileIn = open("/tmp/utilityFileForCGI_IN.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1) {
		std::cout << "Error CGI" << std::endl;
		exit(1); // Fix throw
	}
}

void	CGI::executeCGI(std::string &body) {
	_convertEnvironment();
	int		pidStatus;
	int		returnValue;
	long	executableStart;
	
	returnValue = write(this->_fileIn, body.c_str(), body.length());
	if (close(this->_fileIn) == -1)
		exit(1); // check for other throw
	if (returnValue == -1)
		exit(1); // check for other throw
	if ((_pid = fork()) == -1)
		exit(1); // check for other throw
	if (_pid == 0) {
		if ((this->_fileOut = open("/tmp/utilityFileForCGI_OUT.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1)
			exit(1); // check for other throw
		if (dup2(this->_fileOut, STDOUT_FILENO) == -1)
			exit(1); // check for other throw
		if (close(this->_fileOut) == -1)
			exit(1); // check for other throw
		if ((this->_fileIn = open("/tmp/utilityFileForCGI_IN.txt", O_RDONLY, S_IRWXU)) == -1)
			exit(1); // check for other throw
		if (dup2(this->_fileIn, STDIN_FILENO) == -1) {
			close(this->_fileIn);
			exit(1); // check for other throw
		}
		close(this->_fileIn);
		if (this->_type == PHP)
			_path = "cgi-bin/php-cgi";
		executableStart = _path.rfind('/') + 1;
		std::string executable = _path.substr(executableStart);
		std::string pathStart = _path.substr(0, executableStart);
		if (chdir(pathStart.c_str()) == -1) // if path not excisting
			exit(1); // check for other throw
		const char*	realArgv[2]; // why const if changed later?
		realArgv[0] = executable.c_str();
		realArgv[1] = NULL;
		char *const *argv = const_cast<char *const *>(realArgv); // why cast?
		int ret = execve(argv[0], reinterpret_cast<char *const *>(argv), _env); // execute env var
		if (ret < 0) {
			Utils::freeArray(_env);
			exit(1); // check for other throw
		}
	}
	// std::string ret;
	if (waitpid(0, &pidStatus, 0) == -1)
		exit(1); // check for other throw
	Utils::freeArray(_env);
	if ((this->_fileRet = open("/tmp/utilityFileForCGI_OUT.txt", O_RDONLY)) == -1)
		exit(1); // check for other throw
}

void	CGI::_initEnvironment(Request &request, Server &server) {
	std::stringstream ss;
	std::map<std::string, std::string> CGIHeaders = request.getCGIHeaders();
	std::map<std::string, std::string>::iterator it = CGIHeaders.begin();
	std::map<std::string, std::string> requestHeaders = request.getDefHeaders();

	if (requestHeaders.find("AUTHORIZATION") != requestHeaders.end())
		this->_environment["AUTH_TYPE"] = requestHeaders["AUTHORIZATION"];
	ss << request.getBody().length();
	this->_environment["CONTENT-LENGTH"] = ss.str();
	ss.clear();
	if (request.getBody().empty())
		this->_environment["CONTENT-TYPE"] = "";
	else
		this->_environment["CONTENT-TYPE"] = request.getMethod();
	this->_environment["GATEWAY_INTERFACE"] = "CGI"; 
	this->_environment["PATH_INFO"] = request.getUri() + request.getCGIEnv();
	this->_environment["PATH_TRANSLATED"] = request.getUri();
	this->_environment["REDIRECT_STATUS"] = _setRedirectStatus();
	this->_environment["QUERY_STRING"] = request.getCGIEnv();
	this->_environment["REMOTE_ADDR"] = server.getHost();
	this->_environment["REMOTE_IDENT"] = "ID"; 
	this->_environment["REMOTE_USER"] = "USER"; 
	this->_environment["REQUEST_METHOD"] = request.getMethod();
	this->_environment["REQUEST_URI"] = request.getUri();
	this->_environment["SCRIPT_NAME"] = request.getUri();
	if (_type == PHP)
		this->_environment["SCRIPT_FILENAME"] = "php_tester.php";
	if (requestHeaders.find("HOST") != requestHeaders.end())
		this->_environment["SERVER_NAME"] = requestHeaders["HOST"];
	else
		this->_environment["SERVER_NAME"] = this->_environment["REMOTE_ADDR"];
	ss << server.getPortNumber();
	this->_environment["SERVER_PORT"] = ss.str();
	ss.clear();
	this->_environment["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_environment["SERVER_SOFTWARE"] = "Webserver project RRT";
    for (; it != CGIHeaders.end(); it++) {
        _environment.insert(std::make_pair(it->first, it->second));
	}
}

std::string	CGI::readOutput() {
	char buff[MB];
	int readRet = 1;
	std::string ret;
	while (readRet) {
		bzero(buff, MB);
		if ((readRet = read(this->_fileRet, buff, MB -1)) == -1)
			exit(1);
		ret += buff;
	}
	if (close(this->_fileRet) == -1)
		exit(1);
	return ret;
}

std::string	CGI::_setRedirectStatus() {
	if (this->_type == PHP)
		return ("200");
	else
		return ("CGI");
}

void	CGI::_convertEnvironment() { //  creating our _env var from our _environment map
	std::map<std::string, std::string>::const_iterator it = this->_environment.begin();

	this->_env = new char*[this->_environment.size() + 1];
	if (!_env)
		return ;
	int i = 0;
	for (; it != this->_environment.end(); it++) {
		std::string tmp = it->first + "=" + it->second; // add key to value
		this->_env[i] = strdup(tmp.c_str());
		if (!this->_env[i]) {
			exit(1); // do we have to do this as well?
		}
		++i;
	}
	_env[i] = NULL;
}
