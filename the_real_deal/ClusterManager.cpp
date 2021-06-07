/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClusterManager.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:30:47 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 08:45:23 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ClusterManager.hpp"

ClusterManager::ClusterManager(void)
{
	return;
}

ClusterManager::~ClusterManager(void)
{
	return;
}
void	ClusterManager::configServer(std::string configFilePath)
{
	_config.parseConfigFile(configFilePath.c_str());
	return;
}

ClusterManager::ClusterManager(ClusterManager const &src)
{
	if (this != &src)
		*this = src;
	return;
}

ClusterManager & ClusterManager::operator=(const ClusterManager & src)
{
	_config = src._config;
	// _servers = src._servers;
	// _fd_set = src._fd_set;
	// _fd_size = src._fd_size;
	// _max_fd = src._max_fd;
	return (*this);
}