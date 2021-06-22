/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Connection.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 10:44:14 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/17 14:17:53 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "ConnectionUtils.hpp"

Connection::Connection() :	_timeLastContactInSeconds(0), _acceptFD(-1), _hasFullRequest(false), _bodyBytesSent(0),
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
		this->_timeLastContactInSeconds = obj._timeLastContactInSeconds;
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
	this->_timeLastContactInSeconds = time;
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
	return this->_timeLastContactInSeconds;
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
	this->_timeLastContactInSeconds = 0;
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
	this->_timeLastContactInSeconds = Utils::getTime();
}

void	Connection::sendChunked(const size_t bodylen, const size_t headerlen) {
	size_t	ret = 0;
	if (!this->_headerSend) {
		std::string header = this->_responseString.substr(0, headerlen);
		ret = send(this->_acceptFD, header.c_str(), header.length(), 0);
		if (ret != headerlen) {
			// sigpipe here is being handled elsewhere
			return;
		}
		this->_headerSend = true;
		return;
	}
	else if (bodylen - this->_bodyBytesSent > 0) { // send non-empty chunks
		std::stringstream ss;
		size_t	bytesToSend = std::min((bodylen - this->_bodyBytesSent), size_t(MAX_SEND_SIZE));
		
		ss << std::hex << bytesToSend;
		std::string chunk(ss.str());
		chunk += "\r\n";
		chunk.append(this->_responseString, headerlen + this->_bodyBytesSent, bytesToSend);
		chunk += "\r\n";
		ret = send(this->_acceptFD, chunk.c_str(), chunk.length(), 0);
		if (ret != chunk.length()) {
			// sigpipe here is being handled elsewhere
			return;
		}
		this->_bodyBytesSent += bytesToSend;
	}
	else {
		std::string end("0\r\n\r\n");
		ret = send(this->_acceptFD, end.c_str(), 5, 0);
		if (ret != 5)	{
			// sigpipe here is being handled elsewhere
			return;
		}
		this->resetConnection();
	}
}

std::string	Connection::receive() {
	char buffer[MAX_READ_SIZE + 1];
	int ret;

	bzero(buffer, MAX_READ_SIZE + 1);
	ret = recv(this->_acceptFD, buffer, MAX_READ_SIZE, 0);
	if (ret == - 1) {
		std::cout << "Error: recv return -1";
		this->resetConnection();
		this->closeConnection();
	}
	if (ret == 0) {
		this->resetConnection();
		this->closeConnection();
	}
	return buffer;
}

void	Connection::startReading() {
	std::string receivedRequest;

	try {
		receivedRequest = this->receive();
		this->_timeLastContactInSeconds = Utils::getTime();
		this->_acceptBuffer += receivedRequest;
	}
	catch(const std::exception& e) {
		std::cout << "What is this exception going to do?\n";
		std::cerr << e.what() << '\n';
		return;
	}
	if (this->isFullRequest())
		this->_hasFullRequest = true;
}

bool	Connection::isFullRequest() const {
	size_t position;

	position = this->_acceptBuffer.find(HEAD_AND_CONTENT_SEPERATOR);
	if (position == std::string::npos)
		return false;
	if (this->_acceptBuffer.find("Transfer-Encoding: chunked\r\n") != std::string::npos) {
		if (this->_acceptBuffer.find("0\r\n\r\n", position + 4) == this->_acceptBuffer.length() - 5) {
			return true;
		}
		else
			return false;
	}
	if (this->_acceptBuffer.find("Content-length: ") == std::string::npos) // content len not specifie, so there is no body
		return true;
	if (this->_acceptBuffer.find(HEAD_AND_CONTENT_SEPERATOR, position + 4) == std::string::npos) // there is content len, so a body, bu no end of body found
		return false;
	return true;
}