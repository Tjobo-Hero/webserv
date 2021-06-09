/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigReader.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:08:33 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 13:02:25 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigReader.hpp"

ConfigReader::ConfigReader(int argc, char **argv) : _argc(argc), _argv(argv) {
	return;
}

ConfigReader::ConfigReader(ConfigReader const &src) {
	if (this != &src)
		*this = src;
	return;
}

ConfigReader::~ConfigReader(){
	return;
}

ConfigReader&	ConfigReader::operator=(ConfigReader const &obj)
{
	if (this != &obj)
		this->_argc = obj._argc;
		this->_argv = obj._argv;
		// this->_configFile = obj._configFile;
	return *this;
}
void		ConfigReader::openConfigFile()
{
	this->_configFile.open(this->_argv[1]);
	if (!this->_configFile)	{
		throw openFileError("Error: failed to open filepath: ", this->_argv[1]);
	}
}