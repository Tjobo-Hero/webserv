/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:00:58 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/25 13:00:24 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "ServerCluster.hpp"
#include "Webserver.hpp"

int main (int argc, char **argv)
{
	ServerCluster	serverCluster;
	ConfigParser	configParser(argc, argv);
	if (argc == 2)
	{
		system("mkdir -p logs && cd logs && rm -f ./*");
		system("rm -f html_pages/Downloads/Download_* html_pages/Downloads/file_should_exist_after html_pages/Downloads/multiple_same");
		try 
		{
			configParser.openConfigFile();
			configParser.parseTheConfigFile(&serverCluster);
			serverCluster.checkDuplicatePorts();
			serverCluster.startup();
			serverCluster.startListening();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "Error: Please provide a .config file\n";
		std::cout << "Example: ./webserv yourfilename.config" << std::endl;
		return 0;
	}
	return 0;
}