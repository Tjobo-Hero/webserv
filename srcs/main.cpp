/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:00:58 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 10:52:23 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./Parser/ConfigParser.hpp"
#include "ServerCluster/ServerCluster.hpp"
#include "Webserver.hpp"

void	outputErrorMessageAndExitCode(const std::string &errorMessage, int exitCode) {
	std::cerr << "error: " << errorMessage << std::endl;
	exit(exitCode);
}

int main (int argc, char **argv)
{
	ServerCluster	serverCluster;
	ConfigParser	configParser(argv);
	if (argc == 2)
	{
		system("mkdir -p logs && cd logs && rm -f ./*");
		system("rm -f html_pages/Downloads/Download_* html_pages/Downloads/file_should_exist_after html_pages/Downloads/multiple_same");
		try 
		{
			configParser.parseTheConfigFile(&serverCluster);
			serverCluster.setReady();
			serverCluster.listening();
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