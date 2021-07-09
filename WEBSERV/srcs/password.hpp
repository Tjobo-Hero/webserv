#ifndef PASSWORD_HPP
# define PASSWORD_HPP

# include <iostream>
# include "Location.hpp"
# include <vector>

class Password
{
	std::string user;
	std::string password;
	std::map<std::string, std::string> UsersAndPasswords;
	size_t	lineCount;

	public:
		Password();
		~Password();
		std::map<std::string, std::string>	getUsersAndPasswords() const;
		void	findUsersAndPasswords(std::vector<std::string> lines);
		bool	check(std::string line, size_t *placeOfChar);
		void	checkForEmpty();
		bool	checkPassword(std::string line, size_t *placeOfChar);
		bool	checkUsername(std::string line, size_t *placeOfChar);
		bool	checkCharacters(std::string line, size_t *placeOfChar);
		bool	checkLine(std::string line, size_t *placeOfChar);
};

#endif



// bool	checkUsername(string line, size_t *placeOfChar)
// {
// 	for (size_t i = 0 ; i < *placeOfChar; ++i)
// 	{
// 		if (!isdigit(line[i]) && !isalpha(line[i]))
// 		{
// 			cout << "Wrong character: " << line[i] << endl;
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// bool	checkPassword(string line, size_t *placeOfChar)
// {
// 	for (size_t i = *placeOfChar + 1; i < line.size(); ++i)
// 	{
// 		if (!isdigit(line[i]) && !isalpha(line[i]) && line[i] != '$' && line[i] != '/')
// 		{
// 			cout << "Wrong character: " << line[i] << endl;
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// bool	checkCharacters(string line, size_t *placeOfChar)
// {
// 	if (checkUsername(line, placeOfChar) == false)
// 		return(false);
// 	if (checkPassword(line, placeOfChar) == false)
// 		return (false);
// 	return (true);
// }

// bool	check(string line, size_t *placeOfChar)
// {
// 	(*placeOfChar) = line.find(':');
// 	if (*placeOfChar == string::npos)
// 		return (false);
// 	if (checkCharacters(line, placeOfChar) == false)
// 		return (false);
// 	return (true);
// }

// string	setUser(string line, size_t placeOfChar)
// {
// 	return (line.substr(0, placeOfChar));
// }

// string	setPassword(string line, size_t placeOfChar)
// {
// 	return (line.substr(placeOfChar + 1, line.find_first_of("\n\r#;")));
// }

// void	printAll(string user, string password)
// {
// 	cout << "User: " << user << endl;
// 	cout << "Password " << password << endl << endl;
// }

// void	checkForEmpty(string *user, string *password)
// {
// 	if (user->empty())
// 		*user = "admin";
// 	if (password->empty())
// 		*password = strdup("admin");
// }

// int	main(void)
// {
// 	string line;
// 	fstream configFile;
// 	size_t	placeOfChar;
// 	map<string, string>	infoMap;
// 	string user;
// 	string password;

// 	configFile.open("userAndPassword.txt");
// 	while (getline(configFile, line))
// 	{
// 		if (check(line, &placeOfChar))
// 		{
// 			// cout << '[' << placeOfChar << "] " << line << endl;
// 			user = setUser(line, placeOfChar);
// 			password = setPassword(line, placeOfChar);
// 			checkForEmpty(&user, &password);
// 			// printAll(user, password);
// 			// infoMap[user] = password;
// 			A.setMap(user, password);
// 		}
// 		if (placeOfChar == string::npos)
// 			cout << "NOT FOUND\n";
// 	}
// 	A.printMap();
// 	return (0);
// }
