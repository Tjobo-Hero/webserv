/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:07:58 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/07/12 14:53:30 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Libraries.hpp"
#include "Request.hpp"
#include "Server.hpp"

class Server;

class CGI {
	public:
		CGI(std::string &path, Request &request, Server &server);
		CGI();
		CGI(CGI &src);
		~CGI();
		void		executeCGI(std::string &body);
		void		checkForWriteErrors(int returnValue);
		void		startForkForCGIAndExecute();
		void		createForkAndCheckError();
		void		setupInputFileCGI();
		void		setupOutputFileCGI();
		void		openOutputFileCGI();
		void		dupOutputFileCGI();
		void		closeOutputFileCGI();
		void		openInputFileCGI();
		void		dupInputFileCGI();
		void		closeInputFileCGI();
		void		openInputFileCGI_ReadOnly();
		std::string	setupCGIPath();
		void		castAndExecute(std::string executable);
		void		checkExecveError(int ret);
		std::string readOutput();
		void		setupInFile();

	private:
		void	_initializeEnvironment(Request &request, Server &server);
		void	_convertEnvironmentMapToArray();
		void	_convertLoop();
		char*	_createEnvLine(std::map<std::string, std::string>::const_iterator it);
		std::string	_readOutputLoop();

		void	_setAllEnvVariables(Request &request, Server& server);
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