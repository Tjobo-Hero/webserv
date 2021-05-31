/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configreader.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 12:28:55 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Configreader.hpp"
#include "Webserver.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

ConfigReader::ConfigReader(void)
{
	return;
}

ConfigReader::ConfigReader(ConfigReader const &src)
{
	if (this != &src);
		*this = src;
	return;
}

ConfigReader::~ConfigReader(void)
{
	return;
}

ConfigReader&		ConfigReader::operator=(const ConfigReader &obj)
{
	if (this != &obj)
		*this = obj;
	return *this;
}

configVector		ConfigReader::readfile(const char *config_file)
{
	int						ret = READ_BUF_SIZE;
	char					buffer[READ_BUF_SIZE + 1];
	int						fd;
	std::string				file_string = ""; // string to store the buffer 
	configVector			file;

	for (int i = 0; i < READ_BUF_SIZE + 1; i++)
		buffer[i] = '\0';
	if ((fd = open(config_file, O_RDONLY)) < 0)
		throw ConfigReader::NotAValidFileException();
	for (ret = READ_BUF_SIZE; ret > 0; ret = read(fd, buffer, READ_BUF_SIZE))
	{
		buffer[ret] = '\0';
		file_string += buffer;
	}
	// check if read has returned 
	if (ret < 0)
	{
		throw ConfigReader::ReadingFailedException();
	}
	file = ConfigReader::split(file_string, std::string(" \n\t"));
	return file;
	
}

const char	*ConfigReader::NotAValidFileException::what() const throw()
{
	std::perror("Failed to open file: ");
	return;
}

const char	*ConfigReader::ReadingFailedException::what() const throw()
{
	std::perror("Reading failed: ");
	return;
}
