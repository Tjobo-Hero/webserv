/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:18:57 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 15:19:21 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "Webserver.hpp"
#include "Configreader.hpp"
#include "ConfigServer.hpp"

// typedef std::vector<std::string>	configVector;

class Config
{
	private:
	
	std::vector<ConfigServer>	_servers;
	
	public:

		int	parse(const char *filename);
		
		class MissingBrackedAfterDirective : public std::exception {
			virtual const char*	what() const throw();
		};
		class ErrorInServerParsing : public std::exception {
			virtual const char*	what() const throw();
		};

};
#endif