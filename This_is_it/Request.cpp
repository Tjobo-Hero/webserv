/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 14:06:12 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/18 14:51:58 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::string methods[4] = {
	"GET",
	"HEAD",
	"POST",
	"PUT",
};

Request::Request() {}

Request::~Request() {}

Request::Request(const Request &src) {
	if (this != &src)
		*this = src;
}

Request	&Request::operator=(const Request &src) {
	if (this != &src) {
		this->_request = src._request;
		this->_method = src._method;
		this->_uri = src._uri;
		this->_version = src._version;
		this->_CGIEnv = src._CGIEnv;
		this->_body = src._body;
		this->_defHeaders = src._defHeaders;
		this->_status = src._status;
		this->_CGI = src._CGI;
	}
	return *this;
}

Request::Request(std::string request) : _request(request) {
	_bodyLength = 0;
	_contentLength = 0;
	_status = 200;
	parseRequest();
}

std::string	Request::getMethod() const {
	for (int i = 0; i < 4; i++) {
		if (_method == methods[i])
			return methods[i];
	}
	std::string s;
	return s;
}

std::string	Request::getUri() const {
	return _uri;
}

std::map<std::string, std::string>	Request::getDefHeaders() const {
	return _defHeaders;
}

std::map<std::string, std::string>	Request::getCGIHeaders() const {
	return _CGIHeaders;
}

std::string	Request::getBody() const {
	return _body;
}

std::string	Request::getContentType() {
	if (_defHeaders.begin() == _defHeaders.end()) // empty?
		return ("NULL");
	std::map<std::string, std::string>::iterator it = _defHeaders.find("CONTENT-TYPE");
	if (it == _defHeaders.end())
		return ("NULL");
	return (it->second);
}

std::string	Request::getCGIEnv() const {
	return _CGIEnv;
}

int	Request::getStatus() const {
	return _status;
}

void	Request::parseRequest() {
	checkCGI();
	parseRequestLine();
	parseHeaders();
	std::map<std::string, std::string>::iterator it = _defHeaders.find("TRANSFER-ENCODING");
	if (it != _defHeaders.end()) {
		if (it ->second == "chunked")
			parseBody();
	}
	else
		_body = _request.substr(0, _request.length() -2);
	_request.clear();
}

void	Request::checkCGI() {
	if (_request.find(".py") != std::string::npos)
		_CGI = true;
	else if (_request.find(".php") != std::string::npos)
		_CGI = true;
	else if (_request.find(".bla") != std::string::npos)
		_CGI = true;
	else if (_request.find(".cgi") != std::string::npos)
		_CGI = true;
	else if (_request.find(".cgi-bin") != std::string::npos)
		_CGI = true;
	else
		_CGI = false;
}

void	Request::parseRequestLine() { // nog naar kijken want snap niet wat er precies gebeurd
	size_t	pos1;
	size_t	pos2;

	if (_request[0] == ' ' || _request.find("\r\n") == std::string::npos)
		_status = 400;
	pos2 = _request.find(' ');
	_method = _request.substr(0, pos2);
	if (getMethod().empty()) 
		_status = 400;
	pos2 += 1;
	pos1 = _request.find(' ', pos2);
	size_t questionMarkLocation = _request.find('?', pos2);
	if (questionMarkLocation <= pos1) {
		pos1 = _request.find('?');
		_CGI = true;
		_uri = _request.substr(pos2, pos1 - pos2);
		pos2 = _request.find(' ', pos1);
		_CGIEnv = _request.substr(pos1 + 1, pos2 - pos1 - 1);
	}
	else {
		_uri = _request.substr(pos2, pos1 - pos2);
		pos2 = _request.find(' ', pos1);
	}
	pos1 = _request.find("\r\n");
	pos2++;
	_version = _request.substr(pos1, pos1 - pos2);
	_request = _request.substr(pos1 + 2);
}

// void Request::parseHeaders()

// void Request::parseBody() {
// 	size_t begin
// }

bool Request::getCGI() const {
	return _CGI;
}
