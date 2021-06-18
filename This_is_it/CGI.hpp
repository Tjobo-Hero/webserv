/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CGI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:07:58 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/18 13:12:15 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "Request.hpp"
#include "Server.hpp"

class CGI {
	public:
		CGI(std::string &path, Request &request, Server &server);
		CGI();
		CGI(CGI &src);
		~CGI();
		std::string	executeCGI(std::string &body);
		
	private:
		void	_initEnvironment(Request &request, Server &server);
		void	_convertEnvironment();
		
		std::map<std::string, std::string>	_environment;
		char								**_env;
		std::string							_path; // what path?
		pid_t								_pid;
};

#endif