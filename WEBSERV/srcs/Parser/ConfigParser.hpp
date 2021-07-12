/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:50:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/12 13:20:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include "../Webserver.hpp"
#include "../Libraries.hpp"
#include "./Utils/ParserUtils.hpp"
#include "../Server.hpp"
#include "../Location.hpp"
#include "../ServerCluster.hpp"

class ConfigParser
{
		private:

		std::fstream 						_configFile;
		std::vector<std::string>			_configLines;
		std::vector<std::string>::iterator	_it;

		std::vector<int>					_configCount;
		std::vector<int>::iterator			_count_it;
		char								**_argv;
		ConfigParser(void);

	public:

		ConfigParser(char **argv);
		ConfigParser(ConfigParser const &src);
		~ConfigParser();
		ConfigParser&		operator=(ConfigParser const &obj);

		void			openConfigFile();
		void			parseTheConfigFile(ServerCluster *serverCluster);
		void			createArray();
		bool			createLine(std::string *line, size_t *count);
		void			lookingForServer(ServerCluster *serverCluster);
		void			createServer(ServerCluster *serverCluster);
		void			setLocation(Server *newServer);

		/* Config Utils */
		bool			receiveNextLine(std::string *line, size_t *count);
		void			removeComments(std::string *line);
		void			plusIterators();

};

#endif