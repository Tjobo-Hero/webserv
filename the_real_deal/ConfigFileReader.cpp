/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigFileReader.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 10:13:05 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFileReader.hpp"
#include "Webserver.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

ConfigFileReader::ConfigFileReader(void)
{
	return;
}

ConfigFileReader::ConfigFileReader(ConfigFileReader const &src)
{
	if (this != &src)
		*this = src;
	return;
}

ConfigFileReader::~ConfigFileReader(void)
{
	return;
}

ConfigFileReader&		ConfigFileReader::operator=(const ConfigFileReader &obj)
{
	if (this != &obj)
		*this = obj;
	return *this;
}

std::string		ConfigFileReader::readConfigFile(const char *config_file)
{
	int						ret = READ_BUF_SIZE;
	char					buffer[READ_BUF_SIZE + 1];
	int						fd;
	std::string				configFileString = ""; // string to store the buffer 

	for (int i = 0; i < READ_BUF_SIZE + 1; i++)
		buffer[i] = '\0';
	if ((fd = open(config_file, O_RDONLY)) < 0)
	{
		throw ConfigFileReader::NotAValidFileException();
	}
	for (ret = READ_BUF_SIZE; ret > 0; ret = read(fd, buffer, READ_BUF_SIZE))
	{
		buffer[ret] = '\0';
		configFileString += buffer;
	}
	// check if read has returned 
	if (ret < 0)
	{
		throw ConfigFileReader::ReadingFailedException();
		return configFileString;
	}
	// Put the buffer in a vector of strings 
	return configFileString;
}

const char	*ConfigFileReader::NotAValidFileException::what() const throw()
{
	std::perror("Failed to open file: ");
	return NULL;
}

const char	*ConfigFileReader::ReadingFailedException::what() const throw()
{
	std::perror("Reading failed: ");
	return NULL;
}
