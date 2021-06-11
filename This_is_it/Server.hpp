/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 13:57:16 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 10:06:54 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Webserver.hpp"
#include "Error.hpp"

class Server
{
	public:	

		typedef void	(Server::*setter)(std::string&);
		
	private:

		
		int _portNumber;
		size_t _maxBodySize;
		bool _autoIndex;
		std::string _root;
		std::string _errorPage;
		std::string _host;
		std::vector<std::string> _serverNames;
		std::vector<std::string> _indices;
		std::vector<Location*> _locations;
		std::vector<Server*> _alternativeServers;
		std::map<std::string, setter> _typeFunctionMap;
		
		long _socketFD;
		struct sockaddr_in _addr;
		
	public:

		size_t _bodylen;
		// connection connections[NR_OF_CONNECTIONS];
		Server(void);
		Server(Server const &src);
		~Server(void);

		Server&		operator=(Server const &obj);

		void	setPortNumber(const std::string &listen);
		void	setMaxBodySize(const std::string &maxBodySize);
		void	setAutoIndex(const std::string &autoIndex);
		void	setRoot(const std::string &root);
		void	setErrorPage(const std::string &errorPage);
		void	setHost(const std::string &host);
		void	setServerNames(const std::string &serverNames);
		void	setIndices(const std::string &indices);
		void	setAlternativeServers(Server *alternative);

		void	setupRespStr(int index);

		const int						&getPortNumber() const;
		const size_t					&getMaxBodySize() const;
		const bool						&getAutoIndex() const;
		const std::string				&getRoot() const;
		const std::string				&getErrorPage() const;
		const std::string				&getHost() const;
		const std::vector<std::string>	&getServerNames() const;
		const std::vector<std::string>	&getIndices() const;
		const std::vector<Location*>	&getLocations() const;

		const long						&getSocketFD() const;
		const struct sockaddr_in		&getSocketAddress() const;



};

#endif
