/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:59:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 12:39:32 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"


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

} // end of namespace UTILS
