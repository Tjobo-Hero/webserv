/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ParserUtils.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:59:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/16 15:00:45 by timvancitte   ########   odam.nl         */
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
	bool isUserSet = true;
	bool isPasswordSet = true;
	
	size_t delimiterCheck = line.find_first_of(delimiter);
	if (delimiterCheck == std::string::npos)
		throw parseError(" no delimeter between user and password", "check your input");
	size_t userBegin = line.find_first_not_of(delimiter);
	size_t userEnd = line.find_first_of(delimiter, userBegin);
	size_t passwordBegin = line.find_first_not_of(delimiter, userEnd);
	size_t passwordEnd = line.find_first_of(endOfLine, passwordBegin);

	std::cout	<< "UserBegin: " << userBegin << '\n'\
				<< "UserEnd: " << userEnd << '\n'\
				<< "PasswordBegin" << passwordBegin << '\n' \
				<< "PasswordEnd" << passwordEnd << '\n';
	
	if (delimiterCheck < userBegin) { // no user was added
		std::cout << "No user was added so username is set default, username: [" << user << "]" << std::endl;
		user = "admin";
		isUserSet = false;
		passwordBegin = line.find_first_not_of(delimiter, delimiterCheck);
		passwordEnd = line.find_first_of(endOfLine, passwordBegin);
	}
	if (isUserSet == true) {
		user = line.substr(userBegin, userEnd - userBegin);
		user = removeLeadingAndTrailingSpaces(user);
	}
	if (user.empty()) {
		user = "admin";
		std::cout << "No user was added so user name is set default, username: [" << user << "]" << std::endl;
	}
	if (passwordBegin == std::string::npos) {
		std::cout << "No password was set for user: ["<< user << "]" << " default password is set." << std::endl;
		password = "admin";
		isPasswordSet = false;
	}
	if (isPasswordSet == true) {
		password = line.substr(passwordBegin, passwordEnd - passwordBegin);
		password = removeLeadingAndTrailingSpaces(password);
	}
	if (password.empty())
	{
		password = "admin";
		std::cout << "No password was set for user: ["<< user << "]" << "defautl password is set." << std::endl;
	}
	std::cout << "user:" << user << "  password:" << password << std::endl;
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
		throw parseError("missing location path ", lineCount);
	return NULL;
}

std::string		setLocationPath(std::string &startLine, const char beginOfPathCharacter, int lineCount)
{
	size_t bracketPosition = startLine.find_first_of("{", 0);
	size_t forwardslashPosition = startLine.find_first_of(beginOfPathCharacter, 0);
	size_t endoflocationPath = startLine.find_first_of(WHITESPACE, forwardslashPosition);
	size_t checkIfOnlyBlanksBetweenPathAndBracket = startLine.find_first_not_of(WHITESPACE, endoflocationPath);

	if (bracketPosition == std::string::npos || forwardslashPosition == std::string::npos)
		throw parseError("missing block ", lineCount);
	else if (endoflocationPath == std::string::npos) // no space between path and bracket
		startLine = startLine.substr(forwardslashPosition, bracketPosition - forwardslashPosition);
	else if (checkIfOnlyBlanksBetweenPathAndBracket != bracketPosition)
		throw parseError("invalid path, character between path and '{' ", lineCount);
	else
	{
		size_t lengthOfLocationPath = endoflocationPath - forwardslashPosition;
		startLine = startLine.substr(forwardslashPosition, lengthOfLocationPath);
	}
	if (startLine.back() != '/' && beginOfPathCharacter == '/')
		startLine.append("/");
	return startLine;
}

} // End of UTILS Namespace
