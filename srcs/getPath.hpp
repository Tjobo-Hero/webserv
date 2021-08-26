/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getPath.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 15:08:02 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/26 13:42:59 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETPATH_HPP
# define GETPATH_HPP

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
		Location*	checkFileExtensionUriReturn(std::string extension, Location* it);
		std::string	checkFileExtension(std::string extension);
		bool		checkForLocation();
		bool		checkForNoLocationPutRequest();
		void		checkForNoCGIPostRequest();
		void		setVariables();
		
	public:

		getPath(Server &server, Request &request, Response &response);
		getPath(getPath const &src);
		virtual ~getPath();
		getPath&	operator=(getPath const &obj);
		std::string createPath();
		
		// std::string getFilePath(); // need to be const?
		// std::string getRooDir(); // need to be const?
		void	noLocation();
};
#endif