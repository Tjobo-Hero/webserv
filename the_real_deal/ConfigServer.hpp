/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigServer.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:08:22 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 16:02:17 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

#include "Webserver.hpp"
#include "Configreader.hpp"
#include "ConfigUtils.hpp"

# define parseMap std::map<std::string, void (ConfigServer::*)(configVector)> // ?

// ? listen?
typedef struct	s_listen {
	unsigned int	host;
	int				port;
}				t_listen;

class ConfigServer
{
	private:
		int				parseLocation(size_t &i, std::vector<std::string> &file); // ?
		
		// SET MEMBER FUNCTIONS
		void								setListen(std::vector<std::string> element);
		void								setRoot(std::vector<std::string> element);
		void								setServerName(std::vector<std::string> element);
		void								setErrorPage(std::vector<std::string> element);
		void								setClientBodyBufferSize(std::vector<std::string> element);
		void								setCgiParam(std::vector<std::string> element);
		void								setCgiPass(std::vector<std::string> element);
		void								setAllowedMethods(std::vector<std::string> element);
		void								setIndex(std::vector<std::string> element);
		void								setAutoIndex(std::vector<std::string> element);
		void								setAlias(std::vector<std::string> element);
		
		// MEMBER VARIABLES
		std::vector<t_listen>				_listen; // checken wat dit doet
		std::string							_root;
		std::vector<std::string>			_serverName;
		std::map<int, std::string>			_errorPage;
		int									_clientBodyBufferSize;
		std::map<std::string, std::string>	_cgiParam;
		std::string							_cgiPass;
		std::map<std::string, ConfigServer>	_location;
		std::set<std::string>				_allowedMethods; // wat is set?
		std::vector<std::string>			_index;
		bool								_autoIndex;
		std::string							_alias;
		bool								_aliasSet;
		static ConfigServer					_defaultServer;
		static parseMap						serverParsingMap; // wat????
		static parseMap						locationParsingMap;
		static parseMap						_initServerMap(); // WHAT ???
		static parseMap						_initLocationMap(); // ?

	public:

		ConfigServer(void);
		ConfigServer(const ConfigServer &src);
		~ConfigServer(void);

		ConfigServer&		operator=(const ConfigServer &obj);
		int					serverParser(size_t &i, configVector &elements); // ?
		void				passMembers(ConfigServer &server) const; // ?


		class	ExceptionInvalidArguments: public std::exception {
			virtual const char	*what() const throw();
		};

		static ConfigServer					_initDefaultServer(const char *filename); // ?
		friend	std::ostream &operator<<(std::ostream &out, const ConfigServer &server); // ?
		
		// GETTER MEMBER FUNCTIONS

		std::vector<t_listen>				getListen() const; // port to listen on
		std::string							getRoot() const; // ?
		std::vector<std::string>   			getServerName() const; // Name of the server
		std::map<int, std::string>			getErrorPage() const; // Path to error page
		int									getClientBodyBufferSize() const; // Max body size request
		std::map<std::string, std::string>	getCgiParam() const; // ?
		std::string							getCgiPass() const; // ?
		std::map<std::string, ConfigServer> getLocation() const; // Location of files index etc. 
		std::set<std::string>				getAllowedMethods() const; // Allowed methodes on Server GET SET PUT etc.
		std::vector<std::string>			getIndex() const; // name of index, weg page html
		bool								getAutoIndex() const; //  ?
		std::string							getAlias() const; // ?
		bool								getAliasSet() const; // ?
		static ConfigServer					&getDefaultServer(); // ? Why default server if we can't run the program without an argument
	
		ConfigServer						getLocationForRequest(std::string const path, std::string &locationPath); // ?
};

#endif