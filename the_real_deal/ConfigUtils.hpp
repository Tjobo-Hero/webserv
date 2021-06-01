/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/01 14:18:29 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/01 14:51:12 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGUTILS_HPP
# define CONFIGUTILS_HPP

#include "Webserver.hpp"

bool			isDigitString(const std::string &str);
int				ft_atoi(const char *str);
unsigned int	strToIp(std::string strIp);
#endif