/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigFileReader.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/04 14:47:58 by timvancitte   ########   odam.nl         */
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

configFileVector		ConfigFileReader::splitConfigFile(std::string configFileString, std::string charset)
{
	configFileVector configFileElements;

	configFileString += charset[0]; // put an end character so we know were at the end of the file
	std::string::size_type	start = configFileString.find_first_not_of(charset, 0);
	std::string::size_type	end = 0;
	while (1)
	{
		end = configFileString.find_first_of(charset, start);
		if (end == std::string::npos)
			break;
		std::string s = configFileString.substr(start, end - start);
		configFileElements.push_back(s);
		if ((start = configFileString.find_first_not_of(charset, end)) == std::string::npos)
			break;
	}
	return configFileElements;
}

configFileVector		ConfigFileReader::readConfigFile(const char *config_file)
{
	int						ret = READ_BUF_SIZE;
	char					buffer[READ_BUF_SIZE + 1];
	int						fd;
	std::string				configFileString = ""; // string to store the buffer 
	configFileVector		configFileElements;

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
		return configFileElements;
	}
	// Put the buffer in a vector of strings 
	// std::cout << configFileString << std::endl;
	configFileElements = ConfigFileReader::splitConfigFile(configFileString, std::string(" \n\t"));
	return configFileElements;
	
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
