/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/13 10:40:33 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "../Webserver.hpp"
# include "../Libraries.hpp"
# include "..//Utils/Utils.hpp"
# include "../Server.hpp"
# include "../Location.hpp"
# include "../ServerCluster/ServerCluster.hpp"

class ConfigParser
{
	private:
		char									**_argv;
		std::fstream 							_configFile;
		std::map<int, std::string>				_configLines;
		std::map<int, std::string>::iterator	_it;
		ConfigParser();

	public:
		ConfigParser(char **argv);
		ConfigParser(ConfigParser const &src);
		~ConfigParser();
		ConfigParser&	operator=(ConfigParser const &obj);

		void	parseTheConfigFile(ServerCluster *serverCluster);
		void	getInfoFromConfigFile();
		void	lookingForServer(ServerCluster *serverCluster);
		void	createServer(ServerCluster *serverCluster);
		void	setLocation(Server *newServer);

		void	configNewServer(Server *newServer);
		void	createKey(bool server, Server *newServer, Location *newLocation);
		void	findServer(std::string key, Server *newServer);
		void	findLocation(std::string key, Location *newLocation);
};

#endif