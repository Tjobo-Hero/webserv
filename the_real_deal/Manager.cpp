/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Manager.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:30:47 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 12:22:59 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"

Manager::Manager(void) : _config(DEFAULT_CONFIG)
{
	return;
}

Manager::~Manager(void)
{
	return;
}
void	Manager::config(std::string config_file)
{
	std::cout << "TEST\n";
	_config.parse(config_file.c_str());
	return;
}

Manager::Manager(Manager const &src)
{
	if (this != &src)
		*this = src;
	return;
}

Manager & Manager::operator=(const Manager & src)
{
	_config = src._config;
	// _servers = src._servers;
	// _fd_set = src._fd_set;
	// _fd_size = src._fd_size;
	// _max_fd = src._max_fd;
	return (*this);
}