/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ResponseHeader.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 10:51:36 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/08/30 10:52:36 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseHeader.hpp"
#include <cstdlib>

ResponseHeader::ResponseHeader(std::string &content, std::string &path, int status, std::string &contentType) {
	setAllow(status);
	setContentLanguage();
	setContentLength(content.length());
	setContentLocation(path, status);
	setContentType(contentType);
	setDate();
	setLastModified(path);
	setLocation(path, status);
	setRetryAfter(status, 10);
	setServer();
	setTransferEncoding();
	setWwwAuthenticate(status);
	setErrorStatus();
}

ResponseHeader::ResponseHeader(const ResponseHeader &src) {
	if (this != &src){
		this->_acceptCharsets = src._acceptCharsets;
		this->_acceptLanguage = src._acceptLanguage;
		this->_allow = src._allow;
		this->_authorization = src._authorization;
		this->_contentLanguage = src._contentLanguage;
		this->_contentLocation = src._contentLocation;
		this->_contentLength = src._contentLength;
		this->_contentType = src._contentType;
		this->_date = src._date;
		this->_host = src._host;
		this->_lastModified = src._lastModified;
		this->_location = src._location;
		this->_referer = src._referer;
		this->_retryAfter = src._retryAfter;
		this->_server = src._server;
		this->_transferEncoding = src._transferEncoding;
		this->_wwwAuthenticate = src._wwwAuthenticate;
		this->_errorStatus = src._errorStatus;
	}
}

ResponseHeader::~ResponseHeader() {}

ResponseHeader	&ResponseHeader::operator=(const ResponseHeader &src) {
	if (this != &src) {
		this->_acceptCharsets = src._acceptCharsets;
		this->_acceptLanguage = src._acceptLanguage;
		this->_allow = src._allow;
		this->_authorization = src._authorization;
		this->_contentLanguage = src._contentLanguage;
		this->_contentLocation = src._contentLocation;
		this->_contentLength = src._contentLength;
		this->_contentType = src._contentType;
		this->_date = src._date;
		this->_host = src._host;
		this->_lastModified = src._lastModified;
		this->_location = src._location;
		this->_referer = src._referer;
		this->_retryAfter = src._retryAfter;
		this->_server = src._server;
		this->_transferEncoding = src._transferEncoding;
		this->_wwwAuthenticate = src._wwwAuthenticate;
		this->_errorStatus = src._errorStatus;
	}
	return *this;
}

void	ResponseHeader::setErrorStatus(void) {
	_errorStatus.insert(std::pair<int, std::string>(200, "Ok"));
 	_errorStatus.insert(std::pair<int, std::string>(201, "Created"));
 	_errorStatus.insert(std::pair<int, std::string>(204, "No content"));
 	_errorStatus.insert(std::pair<int, std::string>(400, "Bad Reguest Error"));
 	_errorStatus.insert(std::pair<int, std::string>(401, "Unauthorized"));
 	_errorStatus.insert(std::pair<int, std::string>(403, "Forbidden"));
 	_errorStatus.insert(std::pair<int, std::string>(404, "Not Found"));
 	_errorStatus.insert(std::pair<int, std::string>(405, "Method Not Allowed"));
 	_errorStatus.insert(std::pair<int, std::string>(413, "Payload too large"));
 	_errorStatus.insert(std::pair<int, std::string>(503, "Service unavalable"));
}

std::string	ResponseHeader::getHeader(int status) {
	std::string header;

	header = "HTTP/1.1 " + std::to_string(status) + " " + createStatusMessage(status) + "\r\n";
	header += writeHeader();
	return (header);
}

std::string	ResponseHeader::createStatusMessage(int status) {
	std::map<int, std::string>::iterator it;

	it = this->_errorStatus.find(status);
	if (it != this->_errorStatus.end())
		return it->second;
	return "Unknown Error";
}


std::string	ResponseHeader::writeHeader() {
	std::string header;

	if (this->_allow.empty() == false)
		header += "Allow: " + this->_allow + ENDOFLINE;
	if (this->_contentLanguage.empty() == false)
		header += "Content-Language: " + this->_contentLanguage + ENDOFLINE;
	if (strtol(this->_contentLength.c_str(), NULL, 10) < MAXSENDSIZE)
		header += "Content-Length: " + this->_contentLength + ENDOFLINE;
	else
		header += "Transfer-Encoding: " + this->_transferEncoding + ENDOFLINE;
	if (this->_contentLocation.empty() == false)
		header += "Content-Location: " + this->_contentLocation + ENDOFLINE;
	if (this->_contentType.empty() == false)
		header += "Content-Type: " + this->_contentType + ENDOFLINE;
	if (this->_date.empty() == false)
		header += "Date: " + this->_date + ENDOFLINE;
	if (this->_lastModified.empty() == false)
		header += "Last-Modified: " + this->_lastModified + ENDOFLINE;
	if (this->_location.empty() == false)
		header += "Location: " + this->_location + ENDOFLINE;
	if (this->_retryAfter.empty() == false)
		header += "Retry-After: " + this->_retryAfter + ENDOFLINE;
	if (this->_server.empty() == false)
		header += "Server: " + this->_server + ENDOFLINE;
	if (this->_wwwAuthenticate.empty() == false)
		header += "Www-Authenticate: " + this->_wwwAuthenticate + ENDOFLINE;
	if (this->_specialHeaderKey.empty() == false && this->_specialHeaderValue.empty() == false)
		header += this->_specialHeaderKey + ": " + this->_specialHeaderValue + ENDOFLINE;
	header += ENDOFLINE;
	return (header);
}

void	ResponseHeader::setAllow(const int &status) {
	if (status == 405)
		this->_allow = "Get, Head, Post, Put";
	else
		this->_allow = "";
}

void	ResponseHeader::setContentLanguage() {
	this->_contentLanguage = "en-US";
}

void	ResponseHeader::setContentLength(int length) {
	this->_contentLength = std::to_string(length);
}

void	ResponseHeader::setContentLocation(const std::string &path, int status) {
	if (status != 404)
		this->_contentLocation = path;
}

void	ResponseHeader::setContentType(const std::string &contentType) {
	this->_contentType = contentType;
}

void	ResponseHeader::setDate() {
	char buf[1000];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
	this->_date = buf;
}

void	ResponseHeader::setLastModified(const std::string &path) {
	struct stat stats;
	struct tm *tm;
	char buf[1000];

	if (stat(path.c_str(), &stats) == 0) {
		tm = gmtime(&stats.st_mtime);
		strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", tm);
		this->_lastModified = buf;
	}
}

void	ResponseHeader::setLocation(const std::string &path, int status) {
	if (status == 201 || status / 100 == 3)
		this->_location = path;
}

void	ResponseHeader::setServer() {
	this->_server = "WEBSERV project RRT";
}

void	ResponseHeader::setTransferEncoding() {
	this->_transferEncoding = "Chunked";
}

void	ResponseHeader::setRetryAfter(int status, int number) {
	if (status == 503) {
		char buf[1000];
		time_t now = time(0);
		struct tm tm = *gmtime(&now);
		tm.tm_hour += 1;
		strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
		this->_retryAfter = buf;
	}
	else if (status / 100 == 3)
		this->_retryAfter = std::to_string(number);
	else
		_retryAfter = "";
}

void	ResponseHeader::setWwwAuthenticate(int status) {
	if (status == 401) {
		this->_wwwAuthenticate = "Basic realm=\"Access requires authentification\" charset=\"UTF-8\"";
	}
}
