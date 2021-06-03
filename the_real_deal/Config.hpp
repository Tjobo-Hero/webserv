/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:18:57 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/03 16:28:36 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "Webserver.hpp"
#include "ConfigFileReader.hpp"
#include "ConfigServer.hpp"

// typedef std::vector<std::string>	configVector;

// #define DEFAULT_CONFIG = "./config_files/default.config"

class Config
{
	private:
	
	std::vector<ConfigServer>	_servers;
	
	public:

	Config(std::string defaultServer = DEFAULT_CONFIG);
	Config(Config const &src);
	~Config(void); // virtual of nie?

	Config&		operator=(Config const &obj);

	int	parseConfigFile(const char *filename);
	std::vector<ConfigServer>	getServer() const;
	std::vector<t_listen>		getListen() const;
	
	// friend	std::ostream				&operator<<(std::ostream &out, const Config &config);

	class MissingBrackedAfterDirective : public std::exception {
		virtual const char*	what() const throw();
	};
	class ErrorInServerParsing : public std::exception {
		virtual const char*	what() const throw();
	};

	// std::ostream	&operator<<(std::ostream &out, const Config &config);
};

#endif