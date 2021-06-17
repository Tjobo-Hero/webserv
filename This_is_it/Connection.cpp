/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Connection.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 10:44:14 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/17 12:34:01 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "ConnectionUtils.hpp"

Connection::Connection() :	_timeLastContact(0), _acceptFD(-1), _hasFullRequest(false), _bodyBytesSent(0),
							_headerSend(false), myResponse(NULL) {
	return;
}

Connection::~Connection() {
	close(this->_acceptFD);
	return;
}

Connection::Connection(Connection const &src) {
	if (this != &src)
		*this = src;
	return;
}

Connection&		Connection::operator=(Connection const &obj) {
	if (this != &obj) {
		this->_timeLastContact = obj._timeLastContact;
		this->_acceptFD = obj._acceptFD;
		this->_acceptBuffer = obj._acceptBuffer;
		this->_hasFullRequest = obj._hasFullRequest;
		this->_bodyBytesSent = obj._bodyBytesSent;
		this->_headerSend = obj._headerSend;
		this->_responseString = obj._responseString;
	}
	return *this;
}

void	Connection::setTimeLastRead(const unsigned long &time) {
	this->_timeLastContact = time;
	return;
}

void	Connection::setFD(const long &FD) {
	this->_acceptFD = FD;
	return;
}

void	Connection::setResponseString(const std::string &response) {
	this->_responseString = response;
	return;
}

const unsigned long&	Connection::getTimeLastRead() const {
	return this->_timeLastContact;
}

const long&	Connection::getAcceptFD() const {
	return this->_acceptFD;
}

const bool&	Connection::hasFullRequst() const {
	return this->_hasFullRequest;
}

const std::string&	Connection::getBuffer() const {
	return this->_acceptBuffer;
}

const std::string&	Connection::getResponseString() const {
	return this->_responseString;
}

void	Connection::resetConnection() {
	this->_acceptBuffer.clear();
	this->_hasFullRequest = false;
	this->_bodyBytesSent = 0;
	this->_headerSend = false;
	this->_responseString.clear();
	if (this->myResponse)
		delete (this->myResponse);
	this->myResponse = NULL;
}

void	Connection::closeConnection() {
	close(this->_acceptFD);
	this->_acceptFD = -1;
	this->_timeLastContact = 0;
}

void	Connection::sendData(const size_t bodylen) {
	size_t	headerlen = this->_responseString.find(HEAD_AND_CONTENT_SEPERATOR) + 4;
	if (bodylen < (size_t)MAX_SEND_SIZE) {
		if (send(this->_acceptFD, this->_responseString.c_str(), this->_responseString.length(), 0) == -1) {
			//sigpipe here is being handeld elsewhere, but where?
			return;
		}
		this->resetConnection();
	}
	else // chunked response
		this->sendChunked(bodylen, headerlen);
	this->_timeLastContact = Utils::getTime();
}