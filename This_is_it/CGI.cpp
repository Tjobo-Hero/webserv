/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:12:22 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/18 14:42:50 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI(std::string &path, Request &request, Server &server) :
	_path(path) {
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

std::string	CGI::executeCGI(std::string &body) {
	_convertEnvironment();
	int		fileIn;
	int		pidStatus;
	int		writeRet;
	int		fileOut;
	int		fd;
	long	executableStart;
	
	if ((fileIn = open("/tmp/utilityFileForCGI_IN.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1)
		exit(1); // check for other throw
	writeRet = write(fileIn, body.c_str(), body.length());
	if (close(fileIn) == -1)
		exit(1);
	if (writeRet == -1)
		exit(1);
	if ((_pid = fork()) == -1)
		exit(1);
	if (_pid == 0) {
		if ((fileOut = open("/tmp/utilityFileForCGI_OUT.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1)
			exit(1);
		if (dup2(fileOut, STDOUT_FILENO) == -1)
			exit(1);
		if (close(fileOut) == -1)
			exit(1);
		if ((fileIn = open("/tmp/utilityFileForCGI_IN.txt", O_RDONLY, S_IRWXU)) == -1)
			exit(1);
		if (dup2(fileIn, STDIN_FILENO) == -1) {
			close(fileIn);
			exit(1);
		}
		close(fileIn);
		executableStart = _path.rfind('/') + 1;
		std::string executable = _path.substr(executableStart);
		std::string pathStart = _path.substr(0, executableStart);
		if (chdir(pathStart.c_str()) == -1) // if path not excisting
			exit(1);
		const char*	realArgv[2]; // why const if changed later?
		realArgv[0] = executable.c_str();
		realArgv[1] = NULL;
		char *const *argv = const_cast<char *const *>(realArgv); // why cast?
		int ret = execve(argv[0], reinterpret_cast<char *const *>(argv), _env); // execute env var
		if (ret < 0) {
			free_array(_env);
			exit(1);
		}
	}
	std::string ret;
	if (waitpid(0, &pidStatus, 0) == -1)
		exit(1);
	free_array(_env);
	if ((fd = open("/tmp/utilityFileForCGI_OUT.txt", O_RDONLY)) == -1)
		exit(1);
	char buff[MB];
	int readRet = 1;
	while (readRet)
	{
		bzero(buff, MB);
		if ((readRet = read(fd, buff, MB - 1)) == -1)
			exit(1);
		ret += buff;
	}
	if (close(fd) == -1)
		exit(1);
	return ret;
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
	this->_environment["GATEWAY_INTERFACE"] = "EPIC CGI"; // WHAT??
	this->_environment["PATH_INFO"] = request.getUri() + request.getCGIEnv();
	this->_environment["PATH_TRANSLATED"] = request.getUri();
	this->_environment["QUERY_STRING"] = request.getCGIEnv();
	this->_environment["REMOTE_ADDR"] = server.getHost();
	this->_environment["REMOTE_IDENT"] = "???"; // WHAT??
	this->_environment["REMOTE_USER"] = "???"; // WHAT??
	this->_environment["REQUEST_METHOD"] = request.getMethod();
	this->_environment["REQUEST_URI"] = request.getUri();
	this->_environment["SCRIPT_NAME"] = request.getUri();
	if (requestHeaders.find("HOST") != requestHeaders.end())
		this->_environment["SERVER_NAME"] = requestHeaders["HOST"];
	else
		this->_environment["SERVER_NAME"] = this->_environment["REMOTE_ADDR"];
	ss << server.getPortNumber();
	this->_environment["SERVER_PORT"] = ss.str();
	ss.clear();
	this->_environment["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_environment["SERVER_SOFTWARE"] = "Merel Jonas Thimo Epic webserver huts";
    for (; it != CGIHeaders.end(); it++) {
        _environment.insert(std::make_pair(it->first, it->second));
	}
}

void	CGI::_convertEnvironment() { //  creating our _env var from our _environment map
	std::map<std::string, std::string>::const_iterator it = this->_environment.begin();

	this->_env = new char*[this->_environment.size() + 1];
	if (!_env)
		return ;
	int j = 0;
	for (; it != this->_environment.end(); it++) {
		std::string tmp = it->first + "=" + it->second; // add key to value
		this->_env[j] = strdup(tmp.c_str());
		if (!this->_env[j]) {
			exit(1); // do we have to do this as well?
		}
		j++;
	}
	_env[j] = NULL;
}