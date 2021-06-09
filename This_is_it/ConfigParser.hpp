/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 15:02:33 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include "Webserver.hpp"

class ConfigParser
{
	private:

		std::fstream	_configFile;
	
	public:

		void			parseTheConfigFile();
		LocationBlock	getLocationBlock(std::string &startline, size_t &lineCount);
		
};

#endif