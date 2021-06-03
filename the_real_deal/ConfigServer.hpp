/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:22 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/03 16:28:50 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

#include "Webserver.hpp"
#include "ConfigFileReader.hpp"
#include "ConfigUtils.hpp"

# define parseMap std::map<std::string, void (ConfigServer::*)(configFileVector)> // ?

// ? listen?
typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;


class ConfigServer
{
	private:
		int				locationBlockParser(size_t &index, std::vector<std::string> &file); // ?
		
		// SET MEMBER FUNCTIONS
		void										setListen(std::vector<std::string> parameter);
		void										setRoot(std::vector<std::string> parameter);
		void										setServerName(std::vector<std::string> parameter);
		void										setErrorPage(std::vector<std::string> parameter);
		void										setClientBodyBufferSize(std::vector<std::string> parameter);
		void										setCgiParameter(std::vector<std::string> parameter);
		void										setCgiPass(std::vector<std::string> parameter);
		void										setAllowedMethods(std::vector<std::string> parameter);
		void										setIndex(std::vector<std::string> parameter);
		void										setAutoIndex(std::vector<std::string> parameter);
		void										setAlias(std::vector<std::string> parameter);
		
		// MEMBER VARIABLES
		std::vector<t_listen>						_listen; // checken wat dit doet
		std::string									_root;
		std::vector<std::string>					_serverName;
		std::map<int, std::string>					_errorPage;
		int											_clientBodyBufferSize;
		std::map<std::string, std::string>			_cgiParameter;
		std::string									_cgiPass;
		std::map<std::string, ConfigServer>			_location;
		std::set<std::string>						_allowedMethods; // wat is set?
		std::vector<std::string>					_index;
		bool										_autoIndex;
		std::string									_alias;
		bool										_aliasSet;
		static ConfigServer							_defaultServer;
		static parseMap								serverParsingMap; // wat????
		static parseMap								locationParsingMap;
		static parseMap								_initServerMap(); // WHAT ???
		static parseMap								_initLocationMap(); // ?

	public:

		ConfigServer(void);
		ConfigServer(const ConfigServer &src);
		~ConfigServer(void);

		ConfigServer&								operator=(const ConfigServer &obj);
				
		int											serverBlockParser(size_t &index, configFileVector &configFileElements); // ?
		static ConfigServer							_initDefaultServer(const char *filename); // ?
		void										setDefaultDirectiveParametersIfNotSet(ConfigServer &server) const; // ?
		ConfigServer								getLocationForRequest(std::string const path, std::string &locationPath); // ?
		// static const std::vector<std::string>	HTTPMethods;

		friend	std::ostream &operator<<(std::ostream &out, const ConfigServer &server); // ?
		
		// GETTER MEMBER FUNCTIONS
		std::vector<t_listen>						getListen() const; // port to listen on
		std::string									getRoot() const; // ?
		std::vector<std::string>   					getServerName() const; // Name of the server
		std::map<int, std::string>					getErrorPage() const; // Path to error page
		int											getClientBodyBufferSize() const; // Max body size request
		std::map<std::string, std::string>			getCgiParameter() const; // ?
		std::string									getCgiPass() const; // ?
		std::map<std::string, ConfigServer> 		getLocation() const; // Location of files index etc. 
		std::set<std::string>						getAllowedMethods() const; // Allowed methodes on Server GET SET PUT etc.
		std::vector<std::string>					getIndex() const; // name of index, weg page html
		bool										getAutoIndex() const; //  ?
		std::string									getAlias() const; // ?
		bool										getAliasSet() const; // ?
		static ConfigServer							&getDefaultServer(); // ? Why default server if we can't run the program without an argument
	

		class	ExceptionInvalidArguments: public std::exception {
			virtual const char	*what() const throw();
		};
};

#endif