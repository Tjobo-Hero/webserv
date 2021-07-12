#ifndef USERSANDPASSWORDS_HPP
# define USERSANDPASSWORDS_HPP

# include <iostream>
# include "Location.hpp"
# include <vector>
# include <map>

class UsersAndPasswords
{
	size_t								lineCount;
	std::string							user;
	std::string							password;
	std::string							errorMessage;
	std::map<std::string, std::string>	mapUsersAndPasswords;

	public:
		UsersAndPasswords();
		~UsersAndPasswords();
		std::map<std::string, std::string>	getUsersAndPasswords() const;
		void	findUsersAndPasswords(std::vector<std::string> lines);
		bool	check(std::string line, size_t *placeOfChar);
		void	checkForEmpty();
		bool	checkPassword(std::string line, size_t *placeOfChar);
		bool	checkUsername(std::string line, size_t *placeOfChar);
		bool	checkCharacters(std::string line, size_t *placeOfChar);
		bool	checkLine(std::string line, size_t *placeOfChar);
		bool	errorHandling(int lineCount, std::string error);
};

#endif
