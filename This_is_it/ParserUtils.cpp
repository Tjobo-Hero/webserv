/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:59:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/14 14:23:38 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ParserUtils.hpp"
#include "ConfigParser.hpp"

namespace Utils
{

bool	isEmptyLine(std::string &line) {
	size_t start = line.find_first_not_of(WHITESPACE, 0);
	return (start == std::string::npos) ? true : false;

}

std::string findFirstWord(std::string &line) {
	size_t		start;
	size_t		end;

	start = line.find_first_not_of(WHITESPACE, 0);
	end = line.find_first_of(WHITESPACE, start);
	return line.substr(start, end);

}

std::string removeLeadingSpaces(const std::string &line) {
	size_t start;
	
	start = line.find_first_not_of(WHITESPACE, 0);
	if (start == std::string::npos)
		return "";
	else
		return line.substr(start);
}

std::string removeTrailingSpaces(const std::string &line) {
	size_t end;
	
	end = line.find_last_not_of(WHITESPACE);
	if (end == std::string::npos)
		return "";
	else
		return line.substr(0, end + 1);
}

std::string removeLeadingAndTrailingSpaces(const std::string &line) {
	return removeTrailingSpaces(removeLeadingSpaces(line));
}

void		getKeyValue(std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine)
{
	size_t userBegin = line.find_first_not_of(delimiter);
	size_t userEnd = line.find_first_of(delimiter, userBegin);
	
	user = line.substr(userBegin, userEnd - userBegin);
	user = removeLeadingAndTrailingSpaces(user);
	if (user.empty())
	{
		user = "admin";
		std::cout << "No user was added so user name is set default, username: [" << user << "]" << std::endl;
	}
	size_t passwordBegin = line.find_first_not_of(delimiter, userEnd);
	size_t passwordEnd = line.find_first_of(endOfLine, passwordBegin);

	password = line.substr(passwordBegin, passwordEnd - passwordBegin);
	password = removeLeadingAndTrailingSpaces(password);
	if (password.empty())
	{
		password = "admin";
		std::cout << "No password was set for user: ["<< user << "]" << "defautl password is set." << std::endl;
	}
	std::cout << "User: [" << user << "]" << " password: [" << password << "] was added." << std::endl;
}

std::string		checkLocationPath(std::string &startLine, int lineCount)
{
	startLine.erase(0, startLine.find_first_of(WHITESPACE, 0));
	startLine = removeLeadingAndTrailingSpaces(startLine);
	if (startLine[0] == '*' && startLine[1] == '.')
		return startLine = setLocationPath(startLine, '*', lineCount);
	else if (startLine[0] == '/')
		return startLine = setLocationPath(startLine, '/', lineCount);
	else
	{
		parseError(startLine, lineCount);
	}
	return NULL;
}

std::string		setLocationPath(std::string &startLine, const char beginOfPathCharacter, int lineCount)
{
	size_t bracketPosition = startLine.find_first_of("{", 0);
	size_t forwardslashPosition = startLine.find_first_of(beginOfPathCharacter, 0);
	size_t endoflocationPath = startLine.find_first_of(WHITESPACE, forwardslashPosition);
	size_t checkIfOnlyBlanksBetweenPathAndBracket = startLine.find_first_not_of(WHITESPACE, endoflocationPath);

	if (bracketPosition == std::string::npos || forwardslashPosition == std::string::npos)
	{
		parseError(startLine, lineCount);
	}
	else if (endoflocationPath == std::string::npos) // no space between path and bracket
		startLine = startLine.substr(forwardslashPosition, bracketPosition - forwardslashPosition);
	else if (checkIfOnlyBlanksBetweenPathAndBracket != bracketPosition)
	{
		parseError(startLine, lineCount);
	}
	else
	{
		size_t lengthOfLocationPath = endoflocationPath - forwardslashPosition;
		startLine = startLine.substr(forwardslashPosition, lengthOfLocationPath);
	}
	if (startLine.back() != '/' && beginOfPathCharacter == '/')
	{
		std::cout << "BACK PATH: " << startLine.back() << std::endl;
		startLine.append("/");
	}
	std::cout << "location path: [" << startLine << "]" << std::endl;
	return startLine;
}

} // End of UTILS Namespace
