/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerBlock.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:18:20 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 10:48:37 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerBlock.hpp"

// ServerBlock::ServerBlock(void){
// 	return;
// }

ServerBlock::ServerBlock(ServerConfiguration serverConfiguration) : _host(serverConfiguration._directives["listen"])
{
	// this->_host = serverConfiguration._directives["listen"];
	this->_port = "";
	this->_socket = -1;
	this->_configuration = serverConfiguration;
	std::fill(reinterpret_cast<unsigned char *>(&this->_sockaddr), reinterpret_cast<unsigned char *>(&this->_sockaddr) + sizeof(this->_sockaddr), 0);
}

ServerBlock::~ServerBlock(){
	return;
}


ServerBlock&	ServerBlock::operator=(ServerBlock const &obj)
{
	if (this != &obj) {
		this->_host = obj._host;
		this->_port = obj._port;
		this->_socket = obj._socket;
		this->_configuration = obj._configuration;
		this->_sockaddr = obj._sockaddr;
	}
	return *this;
}