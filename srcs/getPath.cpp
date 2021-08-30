/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getPath.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/21 15:07:56 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 10:49:04 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "getPath.hpp"

getPath::getPath(Server &server, Request &request, Response &response) : _server(server), _request(request), _response(response) {
	return;
}

getPath::~getPath() {
	return;
}

Location*	getPath::checkFileExtensionUriReturn(std::string extension, Location* it) {
	if (extension == "error_image.png")
		this->_uri = "/error_image.png";
	else if (extension == "php")
		this->_uri = "/cgi/bin/php-cgi";
	return (it);
}

std::string	getPath::checkFileExtension(std::string extension) {
	if (extension == "*.error_image.png")
		extension.erase(0, 2);
	else if (extension == "*.php") 
		extension.erase(0, 2);
	else
		extension.erase(0, 1);
	return extension;
}


Location*	getPath::findFileExtension() {
	std::vector<Location*> locations = _server.getLocations();

	for (std::vector<Location*>::iterator it = locations.begin(); it != locations.end(); ++it) {
		if ((*it)->getIsFileExtension()) {
			std::string extension = checkFileExtension((*it)->getMatch());
			size_t len = extension.length();
			if (this->_uri.length() >= len && !this->_uri.compare(this->_uri.length() - len, len, extension)) {
				return checkFileExtensionUriReturn(extension, *it);
			}
		}
	}
	return NULL;
}

void	getPath::checkFile() {
	this->_found = this->_uri.find_first_of('/', 1);
	if (this->_uri.find_last_of('/') == 0) {
		this->_locationMatch = "/";
		this->_uri.erase(0, 1);
	}
	else
		this->_locationMatch = this->_uri.substr(0, this->_found);
	if (this->_uri.length() > 1 && this->_locationMatch != "/") {
		if (this->_found != std::string::npos)
			this->_uri.erase(0, this->_found + 1);
		else
			this->_uri.erase(0, this->_found);
	}
}

void	getPath::noLocation() {
	if (this->_uri.find('.') != std::string::npos) // file requested
		checkFile();
	else {// location index requested
		this->_needIndex = true;
		if (this->_uri == "/")
			this->_locationMatch = "/";
		else {
			this->_found = this->_uri.find_first_of('/', 1);
			this->_locationMatch = this->_uri.substr(0, this->_found);
			if (this->_found != std::string::npos)
				this->_uri.erase(0, this->_found + 1);
			else
				this->_uri.erase(0, this->_found);
			if (this->_uri.length() && this->_uri[this->_uri.length() -1] != '/' && this->_uri != "/") // add '/' at end
				this->_uri += "/";
		}	
	}
}

void	getPath::locationExistst() {
	struct stat statBuf = {};
	if (!this->_location->getRoot().empty()) // location has no own root, so we use the server root
		this->_rootDir = this->_location->getRoot();
	else
		this->_rootDir = this->_server.getRoot();
	if (!_location->getCGIPath().empty()) {
		this->_filePath = this->_rootDir + this->_location->getCGIPath();
		this->_response.setCurrentLocation(this->_location);
		return;
	}
	if (this->_needIndex && this->_request.getMethod().compare("PUT") != 0 && this->_location->getAutoIndex())
		checkPut();
	else {
		if (this->_request.getFileType() == PHP) {
			this->_filePath = this->_rootDir;
			return;
		}
		this->_filePath = this->_rootDir + this->_uri;
		if (stat(this->_filePath.c_str(), &statBuf) != 0 && this->_request.getMethod().compare("PUT") != 0)
			this->_response.setStatus(404);
	}
}

void getPath::checkPut() {
	std::vector<std::string>	indices;
	std::vector<std::string>::iterator it;

	struct stat statBuf = {};

	if (!this->_location->getIndices().empty())
		indices = this->_location->getIndices();
	else
		indices = this->_server.getIndices();
	for (it = indices.begin(); it != indices.end(); ++it) {
		if (this->_uri != "/")
			this->_filePath = this->_rootDir + this->_uri + (*it);
		else
			this->_filePath = this->_rootDir + (*it);
		if (stat(this->_filePath.c_str(), &statBuf) == 0)
			break;
	}
	if (it == indices.end()) // all index pages don't exist at requested root
		this->_response.setStatus(404);
}

bool	getPath::checkForLocation() {
	if (!this->_location) {
		noLocation();
		this->_location = this->_server.findLocation(this->_locationMatch);
	}
	else
		this->_uri.erase(0, 1);
	if (checkForNoLocationPutRequest() == true)
		return false;
	checkForNoCGIPostRequest();
	return true;
}

bool	getPath::checkForNoLocationPutRequest() {
	if (!this->_location && this->_request.getMethod().compare("PUT") != 0) {
		this->_response.setStatus(404);
		this->_response.setCurrentLocation(this->_location);
		return true;
	}
	return false;
}

void	getPath::checkForNoCGIPostRequest() {
	if (this->_request.getMethod().compare("POST") == 0 && this->_location->getCGIPath().empty()) { 
		if (!this->_location->getRoot().empty()) // use server root
			this->_rootDir = this->_location->getRoot();
		else
			this->_rootDir = this->_server.getRoot();
		static int nr = 0;
		std::stringstream ss;
		ss << this->_rootDir << "Download_" << nr;
		this->_filePath = ss.str();
		nr++;
	}
	else
		locationExistst();
	this->_response.setCurrentLocation(this->_location);
}

void	getPath::setVariables() {
	this->_location = NULL;
	this->_needIndex = false;
	this->_uri = this->_request.getUri();
	this->_location = findFileExtension();
}

std::string getPath::createPath() {
	setVariables();
	
	if (checkForLocation() == false)
		return ("");
	return this->_filePath;
}