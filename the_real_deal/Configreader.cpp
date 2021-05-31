/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configreader.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 14:52:38 by timvancitte   ########   odam.nl         */
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
	if (this != &src)
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

configVector		ConfigReader::split(std::string str, std::string charset)
{
	configVector elements;

	str += charset[0]; // put an end character so we know were at the end of the file
	std::string::size_type	start = str.find_first_not_of(charset, 0);
	std::string::size_type	end = 0;
	while (1)
	{
		end = str.find_first_of(charset, start);
		if (end == std::string::npos)
			break;
		std::string s = str.substr(start, end - start);
		elements.push_back(s);
		if ((start = str.find_first_not_of(charset, end)) == std::string::npos)
			break;
	}
	// std::vector<std::string>::const_iterator it = elements.begin();
	// int i = 0;
	// for(; it != elements.end(); it++)
	// {
	// 	std::cout << "index " << i << " : ";
	// 	std::cout << *it << std::endl;
	// 	i++;
	// }
	return elements;
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
	// Put the buffer in a vector of strings 
	// std::cout << file_string << std::endl;
	file = ConfigReader::split(file_string, std::string(" \n\t"));
	return file;
	
}

const char	*ConfigReader::NotAValidFileException::what() const throw()
{
	std::perror("Failed to open file: ");
	return NULL;
}

const char	*ConfigReader::ReadingFailedException::what() const throw()
{
	std::perror("Reading failed: ");
	return NULL;
}
