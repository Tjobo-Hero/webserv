/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getPath.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 15:08:02 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/22 15:15:08 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETPATH_HPP
# define GETPATH_HPP

// #include "Webserver.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

class getPath
{
	private:

		Server &_server;
		Request &_request;
		Response &_response;
		std::string _filePath;
		std::string _rootDir;
		std::string _uri;
		std::string _locationMatch;
		size_t	_found;
		Location *_location;
		bool _needIndex;
		
		void	locationExistst();
		void	checkPut();
		void	checkFile();
		Location*	findFileExtension();
		
	public:

		getPath(Server &server, Request &request, Response &response);
		getPath(getPath const &src);
		virtual ~getPath();
		getPath&	operator=(getPath const &obj);
		std::string createPath();
		
		std::string getFilePath(); // need to be const?
		std::string getRooDir(); // need to be const?
		void	noLocation();
};
#endif