/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigFileReader.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:18 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/03 12:21:12 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEREADER_HPP
# define CONFIGFILEREADER_HPP

#include "Webserver.hpp"

# define READ_BUF_SIZE 1024

typedef std::vector<std::string>	configFileVector;

class ConfigFileReader
{
	public:

		ConfigFileReader(void);
		ConfigFileReader(ConfigFileReader const &src);
		~ConfigFileReader(void);

		ConfigFileReader&		operator=(const ConfigFileReader &obj);
		static configFileVector	readConfigFile(const char *config_file);
		static configFileVector	splitConfigFile(std::string configFileString, std::string charset);
	
		class NotAValidFileException : public std::exception {
			virtual const char*	what() const throw();
		};
		class ReadingFailedException : public std::exception{
			virtual const char*	what() const throw();
		};
};
#endif