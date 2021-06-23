/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/23 11:19:06 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include "Webserver.hpp"
#include "Libraries.hpp"
#include "ParserUtils.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "ServerCluster.hpp"

class ConfigParser
{
	private:

		std::fstream _configFile;
		int	_argc;
		char **_argv;
		int _lineCount;
		ConfigParser(void);

	public:

		ConfigParser(int argc, char **argv);
		ConfigParser(ConfigParser const &src);
		~ConfigParser(void);

		ConfigParser&		operator=(ConfigParser const &obj);


		void			parseTheConfigFile(ServerCluster *serverCluster);
		Location*		getLocation(std::string &startline);
		void			openConfigFile();
		std::fstream&	getConfigFile();
		static int				getLineCount();

};

#endif