/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Libraries.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 14:41:31 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/23 11:21:31 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARIES_HPP
#define LIBRARIES_HPP

// All the includes for CPP
# include <string>
# include <iostream>
# include <fstream>
# include <algorithm>
# include <sstream>
# include <stdexcept>
# include <regex>
# include <ios>

// All the includes for C
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>

// Container includes
# include <map>
# include <list>
# include <vector>
# include <set>

// Server includes
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>

// Debug Macros

# define PRINTLOG 1
# define PRINTOUT 1

// Defines 
# define NR_OF_CONNECTIONS 200
# define KB 1024
# define MB (KB * 1024)
# define MAX_SEND_SIZE (7 * MB)
# define MAX_READ_SIZE (7 * MB)
# define DEFAULT_ERROR_PAGE "default_error_page"
# define CONNECTION_TIMEOUT 0 // 0 will make it never time out a connection
# define MAXLOGS 25 // this is to prevent the Log of 100.000 connections, this way it only shows the most recent connections

enum filetype { PY = 1, PHP = 2, BLA = 3, CGIBIN = 4};

// Vars
const std::string WHITESPACE = " \n\r\t\f\v";
const std::string allowedMethods[5] = {"", "HEAD", "GET", "POST", "PUT"};
const std::string HEAD_AND_CONTENT_SEPERATOR = "\r\n\r\n";
const std::string END_OF_LINE = "\r\n";

#endif