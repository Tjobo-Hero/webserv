/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClusterClusterManager.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:00:53 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/03 10:38:30 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTERMANAGER_HPP
# define CLUSTERMANAGER_HPP

#include "Config.hpp"
#include "Webserver.hpp"
#include <string.h>
#include <iostream>

class ClusterManager
{
	private:

		Config	_config;
		
	public:
		ClusterManager(void);
		ClusterManager(const ClusterManager &src);
		~ClusterManager(void);
		
		ClusterManager&	operator=(const ClusterManager &obj);

		void configServer(std::string configFilePath);
		// int	setup(void); 
		
};
#endif