/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:58:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/23 11:27:54 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

// // All the includes for CPP
// # include <string>
// # include <iostream>
// # include <fstream>
// # include <algorithm>
// # include <sstream>
// # include <stdexcept>
// # include <regex>
// # include <ios>


// // All the includes for C
// # include <unistd.h>
// # include <fcntl.h>
// # include <stdio.h>
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <sys/time.h>

// // Container includes
// # include <map>
// # include <list>
// # include <vector>
// # include <set>

// // Server includes
// # include <sys/types.h>
// # include <netinet/in.h>
// # include <sys/socket.h>

// includes
# include "ServerCluster.hpp"
# include "Request.hpp"
# include "CGI.hpp"
# include "Server.hpp"

// Debug Macros

# define PRINTLOG 0
# define PRINTOUT 0

// Defines 
# define NR_OF_CONNECTIONS 200
# define KB 1024
# define MB (KB * 1024)
# define MAX_SEND_SIZE (7 * MB)
# define MAX_READ_SIZE (7 * MB)
# define DEFAULT_ERROR_PAGE "default_error_page"
# define CONNECTION_TIMEOUT 0 // 0 will make it never time out a connection
# define MAXLOGS 25 // this is to prevent the Log of 100.000 connections, this way it only shows the most recent connections

// classes
class ServerCluster;

// Vars
const std::string WHITESPACE = " \n\r\t\f\v";
const std::string allowedMethods[5] = {"", "HEAD", "GET", "POST", "PUT"};
const std::string HEAD_AND_CONTENT_SEPERATOR = "\r\n\r\n";
const std::string END_OF_LINE = "\r\n";

// #include "Connection.hpp" // kan niet zomaar
extern Connection *g_recentConnection;

// #include "Connection.hpp"
enum filetype { PY = 1, PHP = 2, BLA = 3, CGIBIN = 4};

#endif