/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:12:22 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/29 12:14:00 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"
#include "ConnectionUtils.hpp"
#include "Error.hpp"

CGI::CGI(std::string &path, Request &request, Server &server) :
	_path(path),
	_type(request.getFileType()) {
		_initializeEnvironment(request, server);
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

void	CGI::setupInFile() {
	if ((this->_fileIn = open("/tmp/fileForCGI_IN.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1) {
		std::cout << "Error CGI" << std::endl;
		outputErrorMessageAndExitCode("open()", 1);
	}
}

void	CGI::checkForWriteErrors(int returnValue) {
	if (close(this->_fileIn) == -1)
		outputErrorMessageAndExitCode("close()", 1);
	if (returnValue == -1)
		outputErrorMessageAndExitCode("write()", 1);
}

void	CGI::createForkAndCheckError() {
	if ((this->_pid = fork()) == -1)
		outputErrorMessageAndExitCode("fork()", 1);
}

void	CGI::openOutputFileCGI() {
	if ((this->_fileOut = open("/tmp/fileForCGI_OUT.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1)
		outputErrorMessageAndExitCode("open()", 1);
}

void	CGI::dupOutputFileCGI() {
	if (dup2(this->_fileOut, STDOUT_FILENO) == -1)
		outputErrorMessageAndExitCode("dup2()", 1);
}

void	CGI::closeOutputFileCGI() {
	if (close(this->_fileOut) == -1)
		outputErrorMessageAndExitCode("close()", 1);
}

void	CGI::openInputFileCGI() {
	if ((this->_fileIn = open("/tmp/fileForCGI_IN.txt", O_RDONLY, S_IRWXU)) == -1)
		outputErrorMessageAndExitCode("open()", 1);
}

void	CGI::openInputFileCGI_ReadOnly() {
	if ((this->_fileRet = open("/tmp/fileForCGI_OUT.txt", O_RDONLY)) == -1)
		outputErrorMessageAndExitCode("open()", 1);
}

void	CGI::dupInputFileCGI() {
	if (dup2(this->_fileIn, STDIN_FILENO) == -1) {
		closeInputFileCGI();
		outputErrorMessageAndExitCode("dup2()", 1);
	}
}

void	CGI::closeInputFileCGI() {
	if (close(this->_fileIn) == -1)
		outputErrorMessageAndExitCode("close()", 1);
}

void	CGI::setupInputFileCGI() {
	openInputFileCGI();
	dupInputFileCGI();
	closeInputFileCGI();
}

void	CGI::setupOutputFileCGI() {
	openOutputFileCGI();
	dupOutputFileCGI();
	closeOutputFileCGI();
}

std::string	CGI::setupCGIPath() {
	long	executableStart;

	if (this->_type == PHP)
		_path = "cgi-bin/php-cgi";
	executableStart = _path.rfind('/') + 1;
	std::string executable = _path.substr(executableStart);
	std::string pathStart = _path.substr(0, executableStart);
	if (chdir(pathStart.c_str()) == -1)
		outputErrorMessageAndExitCode("chdir()", 1);
	return executable;
}

void	CGI::checkExecveError(int ret) {
	if (ret < 0) {
		Utils::freeArray(_env);
		outputErrorMessageAndExitCode("freeArray()", 1);
	}
}

void	CGI::castAndExecute(std::string executable) {
	const char*	realArgv[2];
	realArgv[0] = executable.c_str();
	realArgv[1] = NULL;
	char *const *argv = const_cast<char *const *>(realArgv);
	int ret = execve(argv[0], reinterpret_cast<char *const *>(argv), _env);
	checkExecveError(ret);
}

void	CGI::startForkForCGIAndExecute() {
	int		pidStatus;

	createForkAndCheckError();
	if (this->_pid == 0) {
		setupOutputFileCGI();
		setupInputFileCGI();
		castAndExecute(setupCGIPath());
	}
	if (waitpid(0, &pidStatus, 0) == -1)
		outputErrorMessageAndExitCode("waitpid()", 1);
}

void	CGI::executeCGI(std::string &body) {
	int		returnValue;
	
	_convertEnvironmentMapToArray();
	returnValue = write(this->_fileIn, body.c_str(), body.length());
	checkForWriteErrors(returnValue);
	startForkForCGIAndExecute();
	Utils::freeArray(_env);
	openInputFileCGI_ReadOnly();
}

void CGI::_setEnvContentType(Request &request) {
	if (request.getBody().empty())
		this->_environment["CONTENT-TYPE"] = "";
	else
		this->_environment["CONTENT-TYPE"] = request.getMethod();
	this->_setEnvPathInfo(request);
}

void CGI::_setEnvGatewayInterface() {
	this->_environment["GATEWAY_INTERFACE"] = "CGI";
	this->_setEnvRedirectStatus();
}

void CGI::_setEnvPathInfo(Request &request) {
	this->_environment["PATH_INFO"] = request.getUri() + request.getCGIEnv();
	this->_setEnvPathTranslated(request);
}

void CGI::_setEnvPathTranslated(Request &request) {
	this->_environment["PATH_TRANSLATED"] = request.getUri();
	this->_setEnvQueryString(request);
}

void CGI::_setEnvRedirectStatus() {
	if (this->_type == PHP)
		this->_environment["REDIRECT_STATUS"] = "200";
	else
		this->_environment["REDIRECT_STATUS"] = "CGI";
	this->_setEnvRemoteAddr();
}

void CGI::_setEnvQueryString(Request &request) {
	this->_environment["QUERY_STRING"] = request.getCGIEnv();
	this->_setEnvRequestMethod(request);
}

void CGI::_setEnvRemoteAddr(Server &server) {
	this->_environment["REMOTE_ADDR"] = server.getHost();
	this->_setEnvServerPort(server);
}

void CGI::_setEnvRemoteAddr() {
	this->_environment["REMOTE_IDENT"] = "ID"; 
	this->_setEnvRemoteUser();
}

void CGI::_setEnvRemoteUser() {
	this->_environment["REMOTE_USER"] = "USER"; 
	this->_setEnvScriptFilename();
}

void CGI::_setEnvRequestMethod(Request &request) {
	this->_environment["REQUEST_METHOD"] = request.getMethod();
	this->_setEnvRequestUri(request);
}

void CGI::_setEnvRequestUri(Request &request) {
	this->_environment["REQUEST_URI"] = request.getUri();
	this->_setEnvScriptName(request);
}

void CGI::_setEnvScriptName(Request &request) {
	this->_environment["SCRIPT_NAME"] = request.getUri();
	this->_setEnvContentLength(request);
}

void CGI::_setEnvServerName(std::map<std::string, std::string> requestDefaultHeaders) {
	if (requestDefaultHeaders.find("HOST") != requestDefaultHeaders.end())
		this->_environment["SERVER_NAME"] = requestDefaultHeaders["HOST"];
	else
		this->_environment["SERVER_NAME"] = this->_environment["REMOTE_ADDR"];
	this->_setEnvAuthType(requestDefaultHeaders);
}

void CGI::_setEnvScriptFilename() {
	if (this->_type == PHP)
		this->_environment["SCRIPT_FILENAME"] = "php_tester.php";
	this->_setEnvServerProtocol();
}

void CGI::_setEnvServerPort(Server &server) {
	std::stringstream ss;
	
	ss << server.getPortNumber();
	this->_environment["SERVER_PORT"] = ss.str();
	ss.clear();
}

void CGI::_setEnvServerProtocol() {
	this->_environment["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_setEnvServerSoftware();
}

void CGI::_setEnvServerSoftware() {
	this->_environment["SERVER_SOFTWARE"] = "Webserver project RRT";
}

void CGI::_createEnvMap(std::map<std::string, std::string> allCGIHeaders) {
	std::map<std::string, std::string>::iterator it = allCGIHeaders.begin();
	
	for (; it != allCGIHeaders.end(); it++) {
		_environment.insert(std::make_pair(it->first, it->second));
	}
}

void	CGI::_setEnvAuthType(std::map<std::string, std::string> requestDefaultHeaders) {
	if (requestDefaultHeaders.find("AUTHORIZATION") != requestDefaultHeaders.end())
		this->_environment["AUTH_TYPE"] = requestDefaultHeaders["AUTHORIZATION"];
}

void	CGI::_setEnvContentLength(Request &request) {
	std::stringstream ss;
	
	ss << request.getBody().length();
	this->_environment["CONTENT-LENGTH"] = ss.str();
	ss.clear();
}

void	CGI::_setAllEnvVariables(Request &request, Server &server) {
	std::map<std::string, std::string> requestDefaultHeaders = request.getDefHeaders();

	this->_setEnvContentType(request);
	this->_setEnvRemoteAddr(server);
	this->_setEnvServerName(requestDefaultHeaders);
	this->_setEnvGatewayInterface();
}

void	CGI::_initializeEnvironment(Request &request, Server &server) {
	std::map<std::string, std::string> allCGIHeaders = request.getCGIHeaders();
	
	this->_setAllEnvVariables(request, server);
	this->_createEnvMap(allCGIHeaders);
}

std::string	CGI::_readOutputLoop() {
	char buff[MB];
	int readRet = 1;
	std::string tmp;

	while (readRet) {
		bzero(buff, MB);
		if ((readRet = read(this->_fileRet, buff, MB -1)) == -1)
			outputErrorMessageAndExitCode("read()", 1);
		tmp += buff;
	}
	return tmp;
}

std::string	CGI::readOutput() {
	std::string returnOutputContent;
	
	returnOutputContent = this->_readOutputLoop();
	if (close(this->_fileRet) == -1)
		outputErrorMessageAndExitCode("close()", 1);
	return returnOutputContent;
}

char*	CGI::_createEnvLine(std::map<std::string, std::string>::const_iterator it) {
	std::string line = it->first + "=" + it->second;
	return strdup(line.c_str());
}

void	CGI::_convertLoop() {
	std::map<std::string, std::string>::const_iterator it = this->_environment.begin();
	
	int i = 0;
	for (; it != this->_environment.end(); it++) {
		this->_env[i] = this->_createEnvLine(it);
		if (!this->_env[i]) {
			outputErrorMessageAndExitCode("malloc()", 1);
		}
		++i;
	}
	this->_env[i] = NULL;
}

void	CGI::_convertEnvironmentMapToArray() {
	this->_env = new char*[this->_environment.size() + 1];
	if (!_env)
		return ;
	this->_convertLoop();
}
