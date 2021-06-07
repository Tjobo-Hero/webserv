/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/01 14:18:29 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 14:50:29 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGUTILS_HPP
# define CONFIGUTILS_HPP

#include "Webserver.hpp"

# define READ_BUF_SIZE 1024


namespace ft
{

	bool			isDigitString(const std::string &str);
	int				atoi(const char *str);
	unsigned int	strToIp(std::string strIp);
	int	getNextLine(int fd, std::string &line);
}

#endif