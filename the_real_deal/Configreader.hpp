/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configreader.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:35:18 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 14:51:14 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGREADER_HPP
# define CONFIGREADER_HPP

#include "Webserver.hpp"

# define READ_BUF_SIZE 1024

typedef std::vector<std::string>	configVector;

class ConfigReader
{
	public:

		ConfigReader(void);
		ConfigReader(ConfigReader const &src);
		~ConfigReader(void);

		ConfigReader&		operator=(const ConfigReader &obj);
		static configVector	readfile(const char *config_file);
		static configVector	split(std::string str, std::string charset);
	
		class NotAValidFileException : public std::exception {
			virtual const char*	what() const throw();
		};
		class ReadingFailedException : public std::exception{
			virtual const char*	what() const throw();
		};
};
#endif