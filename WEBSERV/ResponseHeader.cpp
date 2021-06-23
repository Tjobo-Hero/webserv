/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ResponseHeader.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 10:51:36 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/23 15:12:24 by robijnvanho   ########   odam.nl         */
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
}

ResponseHeader::ResponseHeader(const ResponseHeader &src) {
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
	}
}

ResponseHeader::~ResponseHeader() {
	
}

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
	}
	return *this;
}

std::string	ResponseHeader::getHeader(int status) {
	std::string header;
	
	header = "HTTP/1.1 " + std::to_string(status) + " " + createStatusMessage(status) + "\r\n";
	header += writeHeader();
	return (header);
}

// CHANGE TO NICER CODE!!!!!!!!!!!!!!
std::string	ResponseHeader::createStatusMessage(int status) {
	if (status == 200)
		return ("OK");
	else if (status == 201)
		return ("Created");
	else if (status == 204)
		return ("No content");
	else if (status == 400)
		return ("Bad Request Error");
	else if (status == 401)
		return ("Unauthorized");
	else if (status == 403)
		return ("Forbidden");
	else if (status == 404)
		return ("Not _found");
	else if (status == 405)
		return ("Method Not Allowed");
	else if (status == 413)
		return ("Payload too large");
	else if (status == 503)
		return ("Service unavalable");
	else
		return ("Unknown Error");
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
