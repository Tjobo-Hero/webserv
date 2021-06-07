/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:45:09 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:49:22 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"
#include "Server.hpp"

int main (int argc, char **argv)
{
	Server server;
	
	if (argc == 2)
	{
		try 
		{
			server.configFileParser(argv[1]);
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