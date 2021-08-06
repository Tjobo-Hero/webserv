/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/06 16:50:27 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "../Webserver.hpp"
# include "../Libraries.hpp"
# include "..//Utils/Utils.hpp"
# include "../Server.hpp"
# include "../Location.hpp"
# include "../ServerCluster.hpp"

class ConfigParser
{
	private:
		char									**_argv;
		std::fstream 							_configFile;
		std::map<int, std::string>				_configLines;
		std::map<int, std::string>::iterator	_it;
		ConfigParser(void);

	public:
		ConfigParser(char **argv);
		ConfigParser(ConfigParser const &src);
		~ConfigParser();
		ConfigParser&		operator=(ConfigParser const &obj);

		void			parseTheConfigFile(ServerCluster *serverCluster);
		void			lookingForServer(ServerCluster *serverCluster);
		void			createServer(ServerCluster *serverCluster);
		void			setLocation(Server *newServer);
};

#endif