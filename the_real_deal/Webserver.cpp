/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:38 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 09:02:37 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "ClusterManager.hpp"
#include "Webserver.hpp"

int main (int argc, char **argv)
{
	ClusterManager clusterManager;
	
	if (argc == 2)
	{
		try 
		{
			clusterManager.configServer(argv[1]);
			//
			//
			//
			//
			//
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: Please provide a .config file\n";
		std::cout << "Example: ./webserv yourfilename.config" << std::endl;
		return 0;
	}
	// std::string arg(argv[1]);
	// std::cout << "ARG:" << arg << std::endl;
	// fd_open_file = open(arg.c_str(), O_RDONLY);
	return 0;
}