/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:07:58 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/22 16:53:18 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

// #include "Webserver.hpp"
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
		void		setupIn();
		
	private:
		void	_initEnvironment(Request &request, Server &server);
		void	_convertEnvironment();
		std::string _setRedirectStatus();

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