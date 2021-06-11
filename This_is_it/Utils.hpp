/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 14:54:34 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "Webserver.hpp"

namespace Utils
{
bool		isEmptyLine(std::string &line);
std::string findFirstWord(std::string &line);
std::string removeLeadingSpaces(const std::string &line);
std::string removeTrailingSpaces(const std::string &line);
std::string removeLeadingAndTrailingSpaces(const std::string &line);
void		getKeyValue(std::string &line, std::string &key, std::string &value, const char* delimiter, const char* endOfLine);

}
#endif;
