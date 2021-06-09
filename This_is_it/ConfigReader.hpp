/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigReader.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:08:29 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 12:54:13 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGREADER_HPP
# define CONFIGREADER_HPP

#include "Webserver.hpp"
#include "Error.hpp"

class ConfigReader
{
	private:

		std::fstream _configFile;
		int 	_argc;
		char **_argv;
		ConfigReader();
		
	public:
		ConfigReader(int argc, char **argv);
		ConfigReader(ConfigReader const &src);
		~ConfigReader(void);

		ConfigReader&		operator=(ConfigReader const &src);
		void				openConfigFile();

		

	
};
#endif
