/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   webserver.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:37:40 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 14:01:59 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

// All the includes for CPP
#include <string>
#include <iostream>

// All the includes for C
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// Container includes
#include <map>
#include <list>
#include <vector>

// Server includes
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

// Config
# define DEFAULT_CONFIG	"./config_files/default.config"

// # define READER_BUFFER_SIZE 1024 // optimal read buffer size

#endif