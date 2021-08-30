/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:57:31 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/08/30 11:21:20 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Libraries.hpp"

class Request {
	public:
		friend class Response;
		~Request();
		Request(std::string request);
		Request(const Request &src);
		Request &operator=(const Request &src);
		
		std::string	getMethod();
		std::string	getUri() const;
		std::map<std::string, std::string>	getDefHeaders() const;
		std::map<std::string, std::string>	getCGIHeaders() const;
		std::string	getBody() const;
		std::string getHost();
		std::string	getContentType();
		std::string	getCGIEnv() const;
		bool	getCGI() const;
		int		getStatus() const; // whose status?
		
		void	parseRequest();
		void	parseRequestLine();
		void	parseHeaders();
		void	parseBody();
		void	checkCGI();

		filetype getFileType() const;

	private:
		Request(); 
		std::list<std::string>	_allowedMethods;
		std::string _request;
		std::string _method;
		std::string _uri;
		std::string	_version;
		std::string _CGIEnv;
		std::string _body;
		std::map<std::string, std::string>	_CGIHeaders;
		std::map<std::string, std::string>	_defHeaders;
		int	_status;
		int	_bodyLength;
		int	_contentLength;
		bool	_CGI;
		filetype	_type;
};

#endif