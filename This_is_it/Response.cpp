/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:19:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/22 09:54:44 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "getPath.hpp"
#include "CGI.hpp"

Response::Response(Request &request, Server &server) : _useCGI(request.getCGI()), _body(request.getBody()), _status(request.getStatus()), _contentType(request.getContentType()), _method(request.getMethod()), _fileFD(-1), _isFinished(false) {
	getPath path(server, request, *this);
	this->_path = path.createPath();
	CGI cgiTemp(this->_path, request, server);
	this->_myCGI = cgiTemp;
	this->_errorMessage[204] = "No Content"; //  can this be done before and make it const?
	this->_errorMessage[400] = "Bad Request";
	this->_errorMessage[403] = "Forbidden";
	this->_errorMessage[404] = "Not Found";
	this->_errorMessage[405] = "Method not allowed";
	this->_errorMessage[413] = "Payload too large";
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

bool	Response::checkIfMethodIsAllowd() {
	
}

void	Response::setCurrentLocation(Location *newLocation) {
	this->_currentLocation = newLocation;
	return;
}
