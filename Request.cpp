/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 14:06:12 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/23 14:19:36 by timvancitte   ########   odam.nl         */
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
	_contentLength = -1;
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

std::string Request::getHost() {
	if (this->_defHeaders.begin() == this->_defHeaders.end()) {
		this->_status = 400;
		return "NULL";
	}
	std::map<std::string, std::string>::iterator it = this->_defHeaders.find("HOST");
	if (it == this->_defHeaders.end()) {
		this->_status = 400;
		return "NULL";
	}
	std::string host = it->second;
	std::size_t found = host.find(":");
	if (found != std::string::npos)
		host = host.substr(0, found);
	return host;
}

std::string	Request::getCGIEnv() const {
	return _CGIEnv;
}

int	Request::getStatus() const {
	return _status;
}

filetype Request::getFileType() const
{
	return _type;
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

	if (_request[0] == ' ' || _request.find(END_OF_LINE) == std::string::npos)
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
	pos1 = _request.find(END_OF_LINE);
	pos2++;
	_version = _request.substr(pos1, pos1 - pos2);
	_request = _request.substr(pos1 + 2);
}

void Request::parseHeaders() {
	size_t	position = 0;
	size_t	length;
	std::string header;
	std::string upperHeader;
	std::string value;
	std::map<std::string, std::string>::iterator it;
	bool	loop = true;

	while (loop == true) {
		header.clear();
		value.clear();
		upperHeader.clear();
		if (this->_request.find(":", position) == std::string::npos) {
			this->_status = 400;
			return;
		}
		length = this->_request.find(":", position);
		if (std::isspace(this->_request[length -1])) {
			this->_status = 400;
			return;
		}
		header = this->_request.substr(position, length - position);
		if (std::isspace(this->_request[length + 1]))
			position = length + 2;
		else
			position = length + 1;
		length = this->_request.find(END_OF_LINE, position);
		value = this->_request.substr(position, length - position);
		if (header[0] ==  'X' && header[1] == '-') {
			std::string insert("HTTP_");
			std::replace(header.begin(), header.end(), '-', '_');
			insert.append(header);
			this->_CGIHeaders.insert(std::make_pair(insert, value));
			position = length + 2;
			if (this->_request[position] == '\r' && this->_request[position + 1] == '\n')
				loop = false;
			continue;
		}
		for (int i = 0; header[i]; ++i)
			upperHeader += std::toupper(header[i]);
		it = this->_defHeaders.find(upperHeader);
		if (it != this->_defHeaders.end()) {
			this->_status = 400;
			return;
		}
		this->_defHeaders.insert(std::make_pair(upperHeader, value));
		position = length + 2;
		if (this->_request[position] == '\r' && this->_request[position + 1] == '\n')
			loop = false;
	}
	if (this->_defHeaders.empty()) {
		this->_status = 400;
		return;
	}
	for (it = this->_defHeaders.begin(); it != this->_defHeaders.end(); ++it) {
		if (it->first.compare("CONTENT-LENGTH") == 0) {
			std::stringstream ss;
			ss << std::dec << it->second.c_str();
			ss >> this->_contentLength;
			break;
		}
	}
	this->_request = this->_request.substr(position + 2);
}

void Request::parseBody() {
	size_t begin = 0;
	size_t end;
	
	std::string hex;
	size_t last = this->_request.rfind(END_OF_LINE);
	this->_body = "";
	if (this->_request.compare("0\r\n\r\n") == 0)
		return;
	while (begin != last - 2) {
		end = this->_request.find(END_OF_LINE, begin);
		hex = this->_request.substr(begin, end - begin);
		std::stringstream ss;
		
		int tmp;
		ss << std::hex << hex.c_str();
		ss >> tmp;
		this->_bodyLength += tmp;
		begin = end + 2;
		end = this->_request.find(END_OF_LINE, begin);
		this->_body.append(this->_request, begin, end - begin);
		begin = this->_request.find(END_OF_LINE, end + 2);
		hex.clear();
	}
	if (this->_bodyLength != this->_contentLength && this->_contentLength != -1)
		this->_status = 413;
}

bool Request::getCGI() const {
	return _CGI;
}
