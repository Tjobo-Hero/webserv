/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:57:31 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/18 14:43:57 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>

class Request { // cpp niet af
	public:
		friend class Response;
		~Request();
		Request(std::string request);
		Request(const Request &src);
		Request &operator=(const Request &src);
		
		std::string	getMethod() const;
		std::string	getUri() const;
		std::map<std::string, std::string>	getDefHeaders() const;
		std::map<std::string, std::string>	getCGIHeaders() const;
		std::string	getBody() const;
		std::string	getContentType();
		std::string	getCGIEnv() const;
		bool	getCGI() const;
		int		getStatus() const; // whose status?
		
		void	parseRequest();
		void	parseRequestLine();
		void	parseHeaders();
		void	parseBody();
		void	checkCGI();

	private:
		Request();
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
};

#endif