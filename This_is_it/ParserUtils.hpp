/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/14 09:29:08 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

#include "Webserver.hpp"
#include "Error.hpp"

namespace Utils
{
bool		isEmptyLine(std::string &line);
std::string findFirstWord(std::string &line);
std::string removeLeadingSpaces(const std::string &line);
std::string removeTrailingSpaces(const std::string &line);
std::string removeLeadingAndTrailingSpaces(const std::string &line);
void		getKeyValue(std::string &line, std::string &key, std::string &value, const char* delimiter, const char* endOfLine);
std::string checkLocationPath(std::string &startLine);
std::string setLocationPath(std::string &startLine, const char beginOfPathCharacter);

}
#endif;
