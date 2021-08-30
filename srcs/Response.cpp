/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:19:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 14:05:00 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "getPath.hpp"
#include "./Utils/Utils.hpp"

Response::Response(Request &request, Server &server) :
	_useCGI(request.getCGI()),
	_status(request.getStatus()),
	_body(request.getBody()),
	_contentType(request.getContentType()),
	_method(request.getMethod()),
	_fileFD(-1),
	_isFinished(false) {
		getPath path(server, request, *this);
		this->_path = path.createPath();
		CGI cgiTemp(this->_path, request, server);
		this->_myCGI = cgiTemp;
		setErrorMessages();
		// this->_errorMessage[204] = "No Content"; //  can this be done before and make it const?
		// this->_errorMessage[400] = "Bad Request";
		// this->_errorMessage[403] = "Forbidden";
		// this->_errorMessage[404] = "Not Found";
		// this->_errorMessage[405] = "Method not allowed";
		// this->_errorMessage[413] = "Payload too large";
	return;
}

Response::Response() {
	return;
}

Response::Response(Response const &src) {
	if (this != &src)
		*this = src;
	return;
}

Response::~Response() {
	return;
}

Response&	Response::operator=(Response const &obj) {
	if (this != &obj) {
		this->_response = obj._response;
		this->_content = obj._content;
		this->_path = obj._path;
		this->_contentType = obj._contentType;
		this->_useCGI = obj._useCGI;
		this->_status = obj._status;
		this->_errorMessage = obj._errorMessage;
		this->_method = obj._method;
	}
	return *this;
}

void	Response::setErrorMessages() {
	this->_errorMessage[204] = "No Content"; //  can this be done before and make it const?
	this->_errorMessage[400] = "Bad Request";
	this->_errorMessage[403] = "Forbidden";
	this->_errorMessage[404] = "Not Found";
	this->_errorMessage[405] = "Method not allowed";
	this->_errorMessage[413] = "Payload too large";
}

bool	Response::checkIfMethodIsAllowed() {
	if (!this->_currentLocation)
		return false;
	std::vector<std::string>::iterator it;
	std::vector<std::string> vc = this->_currentLocation->getMethods();
	for (it = vc.begin(); it != vc.end(); ++it) {
		if ((*it) == this->_method)
			return true;
	}
	this->_status = 405;
	return false;
}

void	Response::checkAuthentication(Request &request) {
	if (this->authenticate(request)) {
		std::cout << "Authentication failed" << std::endl;
		return;
	}
}

void	Response::redirectToCorrectMethod(Request &request) {
	if (this->_method == "GET")
		this->readContent();
	else if (this->_method == "HEAD")
		this->headMethod();
	else if (this->_method == "POST")
		this->postMethod(request.getBody());
	else if (this->_method == "PUT")
		putMethod(this->_body);
}

void	Response::setupResponse(Request &request, Server &server) {
	checkAuthentication(request);
	if (checkIfMethodIsAllowed())
		redirectToCorrectMethod(request);
	if (this->_status >= 299) {
		this->errorPage(server);
	}
	return;
}

void	Response::setCurrentLocation(Location *newLocation) {
	this->_currentLocation = newLocation;
	return;
}

void	Response::readContent() {
	struct stat statBuf;

	if (this->_useCGI == true) {
		this->_myCGI.setupInFile();
		return;
	}
	if (stat(this->_path.c_str(), &statBuf) != 0)
		return this->setStatus(404);
	this->_fileFD = open(this->_path.c_str(), O_RDONLY);
	if (this->_fileFD == -1 && this->_status == 200)
		return this->setStatus(403);
	if (stat(_path.c_str(), &statBuf) != 0 && this->_status == 200)
		return this->setStatus(404);
	return;
}

void	Response::finishRead() {
	struct stat statBuf;

	if (this->_useCGI == true) {
		this->_content = this->_myCGI.readOutput();
		return;
	}
	stat(this->_path.c_str(), &statBuf);
	char buf[statBuf.st_size +1];
	bzero(buf, statBuf.st_size +1);
	if (read(this->_fileFD, buf, statBuf.st_size) == -1)
		throw runtimeError("Error: Response::finishRead() function, read failed\n");
	this->_content.reserve(statBuf.st_size + 1);
	for (off_t i = 0; i < statBuf.st_size; ++i)
		this->_content += buf[i];
	close(this->_fileFD);
	this->_fileFD = -1;
	return;
}

void	Response::createErrorPage(std::string *pageData) {
	size_t found = 1;
	while (found != std::string::npos) {
		found = pageData->find("ERROR_CODE");
		if (found == std::string::npos) // isn't this the same as the while loop?
			break;
		std::stringstream stat;
		stat << this->_status;
		std::string statstr = stat.str();
		pageData->replace(found, 10, statstr);
	}
	found = 1;
	while (found != std::string::npos) {
		found = pageData->find("MESSAGE");
		if (found == std::string::npos)
			break;
		std::map<int, std::string>::iterator it = this->_errorMessage.find(this->_status);
		if (it == this->_errorMessage.end())
			pageData->replace(found, 7, "unknown error");
		else
			pageData->replace(found, 7, it->second);
	}
	return;
}

void	Response::errorPage(Server &server) {
	std::string pageData;
	std::string pathToPage;
	struct stat statBuff;

	pathToPage = server.getRoot() + server.getErrorPage();
	if (stat(pathToPage.c_str(), &statBuff) < 0)
		pageData = "Problem serving error.\n Error page does not exist.";
	else {
		this->_fileFD = open(pathToPage.c_str(), O_RDONLY);
		if (this->_fileFD < 0)
			pageData = "Problem serving error.\n Cannot open error page.";
		else
			return;
	}
	this->_content.clear();
	if (this->_method != "HEAD")
		this->_content = pageData;
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status) + this->_content;
	this->_isFinished = true;
	return;
}

void	Response::finishErrorPage(Server &server) {
	struct stat statBuf;
	std::string pathToPage;
	pathToPage = server.getRoot() + server.getErrorPage();
	std::string pageData;

	stat(pathToPage.c_str(), &statBuf);
	char buf[statBuf.st_size + 1];
	bzero(buf, statBuf.st_size + 1);
	if (read(this->_fileFD, buf, statBuf.st_size) == -1)
		throw runtimeError("Error: Response::finishErrorPage() function, read fail\n");
	pageData += buf;
	close(this->_fileFD);
	this->_fileFD = -1;
	createErrorPage(&pageData);
	this->_content.clear();
	if (this->_method != "HEAD")
		this->_content = pageData;
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status) + this->_content;
	this->_isFinished = true;
	return;
}

void	Response::getMethod() {
	this->finishRead();
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status) + this->_content;
	this->_isFinished = true;
	return;
}

void	Response::headMethod() {
	this->finishRead();
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status);
	this->_content.clear();
	this->_isFinished = true;
	return;
}

std::string Response::headerValue(size_t startPosition) {
	size_t position;
	size_t position1;
	size_t position2;

	position1 = this->_content.find(' ', startPosition);
	position2 = this->_content.find(";", startPosition);

	position = position1 > position2 ? position2 : position1;
	std::string temp = this->_content.substr(startPosition, position - startPosition);
	return temp;
}

void	Response::parseContent() {
	size_t position;

	if ((position = this->_content.find("Status")) != std::string::npos) {
		std::stringstream ss(headerValue(position + 8));
		ss >> this->_status;
	}
	if ((position = this->_content.find("Content-Type")) != std::string::npos)
		this->_contentType = this->headerValue(position + 14);
	return;
}

void	Response::postMethod(std::string content) {
	this->_postContent = content;
	if (this->_useCGI == true) {
		this->readContent();
		return;
	}
	if (this->_currentLocation->getMaxBodySize() < this->_postContent.length())
		return this->setStatus(413);
	this->_fileFD = open(this->_path.c_str(), O_WRONLY | O_APPEND | O_CREAT);
	if (this->_fileFD == -1 && this->_status == 200)
		this->setStatus(403);
	struct stat statBuf;
	if (stat(this->_path.c_str(), &statBuf) < 0 && this->_status == 200)
		this->setStatus(201);
	return;
}

void	Response::finishPostCGI() {
	int position;
	this->finishRead();
	this->parseContent();
	position = this->_content.find("\r\n\r\n");
	this->_content.erase(0, position + 4);
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status) + this->_content;
	this->_isFinished = true;
	return;
}

void	Response::finishPost() {
	if (this->_useCGI == true)
		return this->finishPostCGI();
	if (write(this->_fileFD, this->_postContent.c_str(), this->_postContent.length()) == -1)
		throw runtimeError("Error: Response::finishPost() function, write failed\n");
	close(this->_fileFD);
	this->_fileFD = -1;
	this->_postContent.clear();
	ResponseHeader header(this->_postContent, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status);
	this->_isFinished = true;
	return;
}

void	Response::putMethod(std::string const &content) {
	std::string::iterator it;

	it = this->_path.end() - 1;
	if ((*it) == '/')
		this->_path.erase(it);
	struct stat statBuf;
	this->_postContent = content;
	if (stat(this->_path.c_str(), &statBuf) < 0 && this->_status == 200)
		this->setStatus(201);
	this->_fileFD = open(this->_path.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0744);
	// std::cout << "3--------------------------------------------------- " << this->_status << std::endl;
	if (this->_fileFD == -1)
		return this->setStatus(403);
	// std::cout << "3--------------------------------------------------- " << this->_status << std::endl;
	return;
}

void	Response::finishPut() {
	int ret = write(this->_fileFD, this->_postContent.c_str(), this->_postContent.length());
	if ((size_t)ret != this->_postContent.length())
		std::cout << "not all was printed, check Response::finishput()" << std::endl;
	close(this->_fileFD);
	this->_fileFD = -1;
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status);
	this->_isFinished = true;
	return;
}

const std::string&	Response::getResponse() const {
	return this->_response;
}

void		Response::setStatus(int status) {
	if (this->_status >= 400)
		return;
	this->_status = status;
}

int			Response::authenticate(Request &request) {
	if (this->_currentLocation == NULL)
		return 0;
	if (this->_currentLocation->getHTPasswordPath().empty()) {
		request._defHeaders["AUTHORIZATION"].clear();
		return 0;
	}
	std::string username, password, str;
	std::string auth = request._defHeaders.at("AUTHORIZATION");
	std::string type, credentials;
	Utils::getKeyValue(auth, type, credentials, " ", "\n\r#;");
	credentials = Utils::base64_decode(credentials);
	Utils::getKeyValue(credentials, username, password, ":", "\n\r#;");
	request._defHeaders["AUTHORIZATION"] = request._defHeaders["AUTHORIZATION"].substr(0, request._defHeaders["AUTHORIZATION"].find_first_of(' '));
	request._defHeaders["REMOTE-USER"] = username;
	if (this->_currentLocation->getAuthMatch(username, password)) {
		std::cout << "AUTHENTICATION SUCCESS" << std::endl;
		return 0;
	}
	this->_status = 401;
	ResponseHeader header(this->_content, this->_path, this->_status, this->_contentType);
	this->_response = header.getHeader(this->_status);
	return 1;
}

std::ostream &operator<<(std::ostream &os, const Response &response) {
	os	<< "_response: " << response._response \
		<< " _content: " << response._content \
		<< " _path: " << response._path \
		<< "_status: " << response._status;
	return os;
}

size_t	Response::getBodySize() const {
	return this->_content.size();
}

const std::string& Response::methodType() const {
	return this->_method;
}

const int& Response::getStatus() const {
	return this->_status;
}

const bool& Response::getUseCGI() const {
	return this->_useCGI;
}

std::string& Response::getBody() {
	return this->_body;
}

CGI&	Response::getCGI() {
	return this->_myCGI;
}

const bool&		Response::isResponseFinished() const {
	return this->_isFinished;
}

