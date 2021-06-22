/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:19:18 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/22 12:53:38 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "Webserver.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "CGI.hpp"

class Response
{
	private:

		bool	_useCGI;
		CGI		_myCGI;
		int			_status; // Status van wat
		std::string	_body; // body van Wat?
		std::string	_response; // response van wat?
		std::string _content; // content van wat
		std::string	_path; // Path van wat?
		std::string	_contentType;
		std::string	_method; // Method svan wat
		std::map<int, std::string>	_errorMessage;
		Location	*_currentLocation;

	public:

		Response(Request &request, Server &server);
		Response(const Response &src);
		virtual ~Response(void);
		Response&	operator=(Response const &obj);
		void		setupResponse(Request &request, Server &server);

		friend std::ostream&	operator<<(std::ostream &os, const Response &response);
	
	private:

		std::string	_postContent; //welke content?
		int	_fileFD;
		bool	_isFinished;
		
		Response(void);
		
		void		postMethod(std::string content);
		void		putMethod(std::string const &content);
		void		errorPage(Server &server); // Wat error page? Wat is de actie?
		void		createErrorPage(std::string *pageData);
		void		readContent(); // Welke content?
		int			authenticate(Request &request); // Authenticate wat?
		void		parseContent(); // Welke content?
		std::string	headerValue(size_t startPosition);
		
	public:
		void	setStatus(int status);
		const std::string&	getResponse() const;
		size_t	getBodySize() const;
		void	setCurrentLocation(Location *newLocation);
		bool	checkIfMethodIsAllowd(); // Veranderd naar const
		const std::string&	methodType() const; // moet dit getMethodType() zijn?
		const int&	getStatus() const; // Status van wat?
		const bool&	getUseCGI() const;
		const bool&	isResponseFinished() const;
		CGI&		getCGI();
		std::string&	getBody(); // Welke body?

		void	finishRead(); // Read van wat?
		void	getMethod();
		void	headMethod();
		void	finishErrorPage(Server &server);
		void	finishPost();
		void	finishPut();
		void	finishPostCGI();
};
#endif