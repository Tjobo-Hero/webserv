/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 13:03:38 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/27 15:27:55 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char **argv)
{
	int fd_open_file;
	if (argc != 2)
	{
		std::cout << "User input" << std::endl;
		return 0;
	}
	std::string arg(argv[1]);
	std::cout << "ARG:" << arg << std::endl;
	fd_open_file = open(arg.c_str(), O_RDONLY);
	return 0;
}