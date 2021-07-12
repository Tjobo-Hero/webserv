/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/12 13:19:20 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

#include "../../Error.hpp"

namespace Utils
{
	bool		skipEmptyLine(std::string *line);
	void		removeSpacesBeforeAfter(std::string *line);
	std::string findFirstWord(std::string &line);

	std::string checkLocationPath(std::string &startLine, int lineCount);
	// std::string	lookForBracket(std::string &startLine, int lineCount);
	// std::string	lookForEnd(std::string &startLine, size_t pos_bracket, int lineCount);
	// std::string	lookForWhitespaces(std::string &startLine, size_t pos_char, size_t pos_end, size_t pos_bracket, int lineCount);
	// std::string	setLocationPath(std::string &startLine, size_t start, size_t end);

void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine);


}
#endif
