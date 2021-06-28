/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:07:58 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/28 15:56:23 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Libraries.hpp"
#include "Request.hpp"
#include "Server.hpp"

class CGI {
	public:
		CGI(std::string &path, Request &request, Server &server);
		CGI();
		CGI(CGI &src);
		~CGI();
		void		executeCGI(std::string &body);
		std::string readOutput();
		void		setupInFile();
		
	private:
		void	_initializeEnvironment(Request &request, Server &server);
		void	_convertEnvironmentMapToArray();
		void	_convertLoop();
		char*	_createEnvLine(std::map<std::string, std::string>::const_iterator it);
		std::string	_readOutputLoop();

		void	_setEnvContentType(Request &request);
		void	_setEnvPathInfo(Request &request);
		void	_setEnvPathTranslated(Request &request);
		void	_setEnvQueryString(Request &request);
		void	_setEnvRequestMethod(Request &request);
		void	_setEnvRequestUri(Request &request);
		void	_setEnvScriptName(Request &request);
		void	_setEnvContentLength(Request &request);
		void	_setEnvRemoteAddr(Server &server);
		void	_setEnvServerPort(Server &server);
		void	_setEnvServerName(std::map<std::string, std::string> requestDefaultHeaders);
		void	_setEnvAuthType(std::map<std::string, std::string> requestDefaultHeaders);
		void	_createEnvMap(std::map<std::string, std::string> AllCGIHeaders);
		void	_setEnvGatewayInterface();
		void	_setEnvRedirectStatus();
		void	_setEnvRemoteAddr();
		void	_setEnvRemoteUser();
		void	_setEnvScriptFilename();
		void	_setEnvServerProtocol();
		void	_setEnvServerSoftware();

		int	_fileIn;
		int	_fileOut;
		int	_fileRet;
		
		std::map<std::string, std::string>	_environment;
		char								**_env;
		std::string							_path; // what path?
		pid_t								_pid;
		filetype							_type;
};

#endif