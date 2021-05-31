/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:22 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 15:22:52 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

#include "Webserver.hpp"

class ConfigServer
{
	public:

		ConfigServer(void);
		ConfigServer(const ConfigServer &src);
		~ConfigServer(void);

		ConfigServer&		operator=(const ConfigServer &obj);
		int					ServerParser(size_t &i, std::vector<std::string> &elements);
		
		private:

			std::
		
};

#endif