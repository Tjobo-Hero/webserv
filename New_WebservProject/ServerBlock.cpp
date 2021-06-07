/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerBlock.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:18:20 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:56:14 by timvancitte   ########   odam.nl         */
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
	if (this != &obj)
		std::cout << "asdf" << std::endl;
	return *this;
}