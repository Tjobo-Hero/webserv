/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getKeyValue.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:59:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/12 14:54:32 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{

	std::string splitUserFromString(const std::string &line, const char* delimiter) {
		std::string result;

		result = line.substr(0, (line.find_first_of(delimiter)));
		return result;
	}

	std::string splitPasswordFromString(const std::string &line, const char* delimiter, const char* endOfLine) {
		std::string result;
		result = line.substr(line.find_first_of(delimiter) + 1, line.find_first_of(endOfLine));
		return result;
	}

	bool		checkIfStringIsEmpty(const std::string &string) {
		return string.empty();
	}

	std::string removeSpacesFromString(std::string string) {
		string.erase(std::remove_if(string.begin(), string.end(), ::isspace), string.end());
		return string;
	}

	bool		checkIfUserAndPasswordInputIsValid(const std::string &line) {
		std::regex regex("^[a-zA-Z0-9._]*:{1}[a-zA-Z0-9._]*$");
		return std::regex_match(line, regex);
	}

	void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine)
	{
		if (checkIfUserAndPasswordInputIsValid(line) == false)
			throw parseError("regex check returns false", "please check your username and password input");
		user = splitUserFromString(line, delimiter);
		password = splitPasswordFromString(line, delimiter, endOfLine);
		if (checkIfStringIsEmpty(user) == true) {
			user = "admin";
			std::cout << "No user was added. Default username is set: [" << user << "]" << std::endl;
		}
		if (checkIfStringIsEmpty(password) == true) {
			std::cout << "No password was set for user: ["<< user << "]" << " default password is set." << std::endl;
			password = "admin";
		}
	}
}
