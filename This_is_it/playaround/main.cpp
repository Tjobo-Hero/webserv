/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:37:24 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 12:29:23 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>


const std::string WHITESPACE = " \n\r\t\f\v";

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

int main()
{
	std::string line = "   asdf :     ";
	std::string user;
	std::string password;
	const char*	delimiter = ":";
	const char* endOfFile = "\n\r#;";

	size_t userBegin = line.find_first_not_of(delimiter);
	size_t userEnd = line.find_first_of(delimiter, userBegin);
	
	user = line.substr(userBegin, userEnd - userBegin);
	user = removeLeadingAndTrailingSpaces(user);
	if (user.empty())
	{
		std::cout << "No user added" << std::endl;
		return 1;
	}
	size_t passwordBegin = line.find_first_not_of(delimiter, userEnd);
	size_t passwordEnd = line.find_first_of(endOfFile, passwordBegin);

	password = line.substr(passwordBegin, passwordEnd - passwordBegin);
	password = removeLeadingAndTrailingSpaces(password);
	if (password.empty())
	{
		std::cout << "No password for: " + user + "added" << std::endl;
		return 1;
	}

	std::cout << "User: [" << user << "]" << " password: [" << password << "]" << std::endl;
	
	return 0;
}