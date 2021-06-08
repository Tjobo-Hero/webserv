/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerConfiguration.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:20:56 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:49:08 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfiguration.hpp"

ServerConfiguration::ServerConfiguration() {
	
	this->_directives["listen"] = "80";
	return ;
}

ServerConfiguration::ServerConfiguration(ServerConfiguration const &src)
{
	if (this != &src)
		*this = src;
}

ServerConfiguration::~ServerConfiguration(){
	return;
}

ServerConfiguration&		ServerConfiguration::operator=(ServerConfiguration const &obj) {
	if (this != &obj)
		std::cout << "BEL DE WOUTEN" << std::endl;
	return *this;
}