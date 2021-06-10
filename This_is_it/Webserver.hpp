/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:58:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/10 14:56:42 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

// All the includes for CPP
# include <string>
# include <iostream>
# include <fstream>
# include <algorithm>
# include <sstream>


// All the includes for C
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

// Container includes
# include <map>
# include <list>
# include <vector>
# include <set>

// Server includes
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>

// Defines 
#define NR_OF_CONNECTIONS 200
#define DEFAULT_ERROR_PAGE "default_error_page"

const std::string WHITESPACE = " \n\r\t\f\v";

// // Config
// // # define DEFAULT_CONFIG	"./config_files/default.config"

// // # define READER_BUFFER_SIZE 1024 // optimal read buffer size


#endif