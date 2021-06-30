/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/30 16:13:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

#include "Error.hpp"

namespace Utils
{
	bool		skipEmptyLine(std::string *line);
	void		removeSpacesBeforeAfter(std::string *line);
	bool		isEmptyLine(std::string &line);
	std::string findFirstWord(std::string &line);
	void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine);
	std::string checkLocationPath(std::string &startLine, int lineCount);
	std::string setLocationPath(std::string &startLine, const char beginOfPathCharacter, int lineCount);
}
#endif
