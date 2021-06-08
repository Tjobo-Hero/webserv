/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:50:02 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/08 13:29:35 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include "Webserver.hpp"
#include "Server.hpp"
#include "ServerConfiguration.hpp"
#include "ConfigUtils.hpp"

#define BLANKS "\t\v "

enum e_context{
	MAIN_BLOCK,
	SERVER_BLOCK,
	ROUTE_BLOCK	
};


enum e_directives{
	LISTEN,
	SERVER_NAME,
	ALIAS,
	ERROR_PAGE,
	LIMIT_EXCEPT,
	AUTOINDEX,
	UPLOAD_STORE,
	EMPTY,
	LAST
};

enum	e_fields{
	LEFT,
	RIGHT
};

static size_t	const hashLen[] = {1, 4, 5};

static const char *blockTypes[] = {"server", "location"};
static const char *mainDirectives[] = {0};
static const char *serverDirectives[] = {"listen", "server_name", "error_page", "client_max_body_size", 0};
static const char *routeDirectives[] = {"index", "limit_except", "root", "autoindex", "upload_store",  "allow_method", "auth_basic", "auth_basic_user_file", "location_max_body_size", 0}; //add cgi later
static const char **allDirectivesString[] = {mainDirectives, serverDirectives, routeDirectives};

class ConfigParser
{
	private:

	public:

		typedef std::queue<ServerConfiguration>	configTokens;
		typedef std::vector<std::string> fields;
		// typedef Server::allServers allServers;

		ConfigParser(void);
		ConfigParser(ConfigParser const &src);
		~ConfigParser(void);
		
		ConfigParser&		operator=(ConfigParser const &obj);

		static void			parseTheConfigFile(char const *configFilePath, Server::allServers &_allServers);
		static int			openConfigFile(const char* configFilePath);
		static void			sampleLine(std::string &line, fields &fields);
		static int			parseTheBlock(int blockIndicator, fields &fields, configTokens tokens);
		static int			addNewBlock(fields &fields, configTokens &tokens, int blockIndicator);
		static int			addNewServerBlock(fields &fields, configTokens &tokens);
		static int			addNewRouteBlock(fields &fields, configTokens &tokens);
		static int			addNewDirective(fields &fields, configTokens &tokens, int blockIndicator);
		static int			addServerDirective(fields &fields, configTokens &tokens);
		static int			addRouteDirective(fields &fields, configTokens &tokens);
		static void			convertTokens(configTokens &tokens, Server::allServers &_allServers)

	class NotAValidFileException : public std::exception {
			virtual const char*	what() const throw();
		};
};

#endif