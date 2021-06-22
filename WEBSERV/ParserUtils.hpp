/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/22 16:28:50 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

// #include "Webserver.hpp"
#include "Error.hpp"

namespace Utils
{
bool		isEmptyLine(std::string &line);
std::string findFirstWord(std::string &line);
std::string removeLeadingSpaces(const std::string &line);
std::string removeTrailingSpaces(const std::string &line);
std::string removeLeadingAndTrailingSpaces(const std::string &line);
void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine);
std::string checkLocationPath(std::string &startLine, int lineCount);
std::string setLocationPath(std::string &startLine, const char beginOfPathCharacter, int lineCount);

}
#endif 
