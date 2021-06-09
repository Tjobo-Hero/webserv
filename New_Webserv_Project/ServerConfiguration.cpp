/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerConfiguration.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:20:56 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 10:45:02 by timvancitte   ########   odam.nl         */
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
	{
		this->_directives = obj._directives;
		this->_allroutes = obj._allroutes;
		this->_errorPages = obj._errorPages;
		this->_routeIndex = obj._routeIndex;	
	}
	return *this;
}