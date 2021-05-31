/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Manager.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:00:53 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 10:45:45 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

#include "Config.hpp"
#include "Webserver.hpp"
#include <string.h>
#include <iostream>

class Manager
{
	private:

		Config	_config;
		
	public:
		Manager(void);
		Manager(const Manager &src);
		~Manager(void);
		
		Manager&	operator=(const Manager &obj);

		void config(std::string fileconf);
		// int	setup(void); 
		
};
#endif