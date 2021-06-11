/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 10:14:31 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include "Webserver.hpp"
#include "Error.hpp"
#include "Utils.hpp"
#include "Server.hpp"

class ConfigParser
{
	private:

		std::fstream _configFile;
		int	_argc;
		char **_argv;
		ConfigParser(void);

	public:

		ConfigParser(int argc, char **argv);
		ConfigParser(ConfigParser const &src);
		~ConfigParser(void);

		ConfigParser&		operator=(ConfigParser const &obj);


		void			parseTheConfigFile();
		// LocationBlock	getLocationBlock(std::string &startline, size_t &lineCount);
		void				openConfigFile();
		std::fstream&		getConfigFile();

};

#endif