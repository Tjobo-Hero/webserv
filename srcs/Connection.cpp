/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Connection.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 10:44:14 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 13:43:13 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "./Utils/Utils.hpp"
#include "Response.hpp"

Connection::Connection() :
	_timeLastContactInSeconds(0),
	_acceptFD(-1),
	_bodyBytesSent(0),
	_hasFullRequest(false),
	_headerSend(false),
	myResponse(NULL) {}

Connection::~Connection()
{
	close(this->_acceptFD);
	return;
}

Connection::Connection(Connection const &src)
{
	if (this != &src)
		*this = src;
	return;
}

Connection&		Connection::operator=(Connection const &obj)
{
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

void	Connection::setTimeLastRead(const unsigned long &time)
{
	this->_timeLastContactInSeconds = time;
}

void	Connection::setFD(const long &FD)
{
	this->_acceptFD = FD;
}

void	Connection::setResponseString(const std::string &response)
{
	this->_responseString = response;
}

const unsigned long&	Connection::getTimeLastRead() const
{
	return this->_timeLastContactInSeconds;
}

const long&	Connection::getAcceptFD() const
{
	return this->_acceptFD;
}

const bool&	Connection::hasFullRequst() const
{
	return this->_hasFullRequest;
}

const std::string&	Connection::getBuffer() const
{
	return this->_acceptBuffer;
}

const std::string&	Connection::getResponseString() const
{
	return this->_responseString;
}

void	Connection::resetConnection()
{
	this->_acceptBuffer.clear();
	this->_hasFullRequest = false;
	this->_bodyBytesSent = 0;
	this->_headerSend = false;
	this->_responseString.clear();
	if (this->myResponse)
		delete (this->myResponse);
	this->myResponse = NULL;
}

void	Connection::closeConnection()
{
	close(this->_acceptFD);
	this->_acceptFD = -1;
	this->_timeLastContactInSeconds = 0;
}

void	Connection::sendNotChunked() {
	if (send(this->_acceptFD, this->_responseString.c_str(), this->_responseString.length(), 0) == -1)
		return;
	this->resetConnection();
}

void	Connection::sendData(const size_t bodylen)
{
	size_t	headerlen = this->_responseString.find(HEAD_AND_CONTENT_SEPERATOR) + 4;
	if (bodylen < (size_t)MAX_SEND_SIZE) {
		sendNotChunked(); // full response
	}
	else // chunked response
		this->sendChunked(bodylen, headerlen);
	this->_timeLastContactInSeconds = Utils::getTime();
}

void	Connection::sendHeader(size_t ret, const size_t headerlen) {
	std::string header = this->_responseString.substr(0, headerlen);
	ret = send(this->_acceptFD, header.c_str(), header.length(), 0);
	if (ret != headerlen)
		return;
	this->_headerSend = true;
	return;
}

std::string	Connection::createChunk(const size_t headerlen, size_t bytesToSend) {
	std::stringstream ss;

	ss << std::hex << bytesToSend;
	std::string chunk(ss.str());
	chunk += "\r\n";
	chunk.append(this->_responseString, headerlen + this->_bodyBytesSent, bytesToSend);
	chunk += "\r\n";
	return chunk;
}

void	Connection::sendFilledChunks(size_t ret, const size_t bodylen, const size_t headerlen) {
	size_t	bytesToSend = std::min((bodylen - this->_bodyBytesSent), size_t(MAX_SEND_SIZE));

	std::string chunk = createChunk(headerlen, bytesToSend);
	ret = send(this->_acceptFD, chunk.c_str(), chunk.length(), 0);
	if (ret != chunk.length())
		return;
	this->_bodyBytesSent += bytesToSend;
}

void	Connection::sendEnd(size_t ret) {
	std::string end("0\r\n\r\n");
	ret = send(this->_acceptFD, end.c_str(), 5, 0);
	if (ret != 5)
		return;
	this->resetConnection();
}

void	Connection::sendChunked(const size_t bodylen, const size_t headerlen) {
	size_t	ret = 0;
	if (!this->_headerSend)
		sendHeader(ret, headerlen);
	else if (bodylen - this->_bodyBytesSent > 0) // send non-empty chunks
		sendFilledChunks(ret, bodylen, headerlen);
	else
		sendEnd(ret);
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

bool	checkForPosition(size_t position) {
	if (position == std::string::npos)
		return false;
	return true;
}

bool	Connection::isChunked(size_t position) const {
	if (this->_acceptBuffer.find("0\r\n\r\n", position + 4) == this->_acceptBuffer.length() - 5)
		return true;
	return false;
}

bool	Connection::isFullRequest() const {
	size_t position;

	position = this->_acceptBuffer.find(HEAD_AND_CONTENT_SEPERATOR);
	if (checkForPosition(position) == false)
		return false;
	if (this->_acceptBuffer.find("Transfer-Encoding: chunked\r\n") != std::string::npos)
		return (this->isChunked(position));
	if (this->_acceptBuffer.find("Content-length: ") == std::string::npos) // There is no body
		return true;
	if (this->_acceptBuffer.find(HEAD_AND_CONTENT_SEPERATOR, position + 4) == std::string::npos) // there is a body, but no end of body found
		return false;
	return true;
}