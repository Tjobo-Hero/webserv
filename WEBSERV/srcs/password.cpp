#include "password.hpp"
#include <map>

Password::Password(void) : lineCount(0){}

Password::~Password(void){}

bool	Password::checkUsername(std::string line, size_t *placeOfChar)
{
	for (size_t i = 0 ; i < *placeOfChar; ++i)
	{
		if (!isdigit(line[i]) && !isalpha(line[i]))
		{
			std::cout << "Wrong character: " << line[i] << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Password::checkPassword(std::string line, size_t *placeOfChar)
{
	for (size_t i = *placeOfChar + 1; i < line.size(); ++i)
	{
		if (!isdigit(line[i]) && !isalpha(line[i]) && line[i] != '$' && line[i] != '/')
		{
			std::cout << "Wrong character in line" << this->lineCount <<  ": " << line[i] << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	Password::checkCharacters(std::string line, size_t *placeOfChar)
{
	if (checkUsername(line, placeOfChar) == false)
		return(false);
	if (checkPassword(line, placeOfChar) == false)
		return (false);
	return (true);
}

bool	Password::checkLine(std::string line, size_t *placeOfChar)
{
	(*placeOfChar) = line.find(':');
	if (*placeOfChar == std::string::npos)
		return (false);
	if (checkCharacters(line, placeOfChar) == false)
		return (false);
	return (true);
}

static std::string	setUser(std::string line, size_t placeOfChar)
{
	return (line.substr(0, placeOfChar));
}

static std::string	setPassword(std::string line, size_t placeOfChar)
{
	return (line.substr(placeOfChar + 1, line.find_first_of("\n\r#;")));
}

void	Password::checkForEmpty(void)
{
	if (this->user.empty())
	{
		this->user = "admin";
		std::cout << "No user was added. Default username is set: [" << user << "]" << std::endl;
	}
	if (this->password.empty())
	{
		this->password = "admin";
		std::cout << "No password was set for user: ["<< user << "]" << " default password is set." << std::endl;

	}

}

void	Password::findUsersAndPasswords(std::vector<std::string> lines)
{
	size_t placeOfDelimiter;
	std::vector<std::string>::iterator x = lines.begin();

	for (; x != lines.end(); ++x)
	{
		++lineCount;
		// Utils::skipEmptyLine(&(*x));
		// 	continue;
		if (checkLine(*x, &placeOfDelimiter))
		{
			this->user = setUser(*x, placeOfDelimiter);
			this->password = setPassword(*x, placeOfDelimiter);
			checkForEmpty();
			this->UsersAndPasswords.insert(std::make_pair(this->user, this->password));
		}
	}
}

std::map<std::string, std::string>	Password::getUsersAndPasswords() const
{
	return this->UsersAndPasswords;
}