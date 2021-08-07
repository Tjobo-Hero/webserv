#include "UsersAndPasswords.hpp"
#include <map>

UsersAndPasswords::UsersAndPasswords(void) : lineCount(0){}

UsersAndPasswords::~UsersAndPasswords(void){}

bool	UsersAndPasswords::errorHandling(int lineCount, std::string error)
{
	std::cout << "Line [" << lineCount << "] Error: " << error << std::endl;
	this->errorMessage.erase(this->errorMessage.size() - 1);
	return (false);
}

bool	UsersAndPasswords::checkUsername(std::string line, size_t *placeOfChar)
{
	for (size_t i = 0 ; i < *placeOfChar; ++i)
	{
		if (!isdigit(line[i]) && !isalpha(line[i]))
			return (errorHandling(this->lineCount, this->errorMessage += line[i]));
	}
	return (true);
}

bool	UsersAndPasswords::checkPassword(std::string line, size_t *placeOfChar)
{
	for (size_t i = *placeOfChar + 1; i < line.size(); ++i)
	{
		if (!isdigit(line[i]) && !isalpha(line[i]) && line[i] != '$' && line[i] != '/')
			return (errorHandling(this->lineCount, this->errorMessage += line[i]));
	}
	return (true);
}

bool	UsersAndPasswords::checkCharacters(std::string line, size_t *placeOfChar)
{
	this->errorMessage = "wrong character ";
	if (checkUsername(line, placeOfChar) == false)
		return(false);
	if (checkPassword(line, placeOfChar) == false)
		return (false);
	return (true);
}

bool	UsersAndPasswords::checkLine(std::string line, size_t *placeOfChar)
{
	if (Utils::skipEmptyLine(line))
		return (false);
	(*placeOfChar) = line.find(':');
	if (*placeOfChar == std::string::npos)
	{
		this->errorMessage = "make sure there is a delimiter character ";
		return (errorHandling(this->lineCount, this->errorMessage += ':'));
	}
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

void	UsersAndPasswords::checkForEmpty(void)
{
	if (this->user.empty())
	{
		this->user = "admin";
		std::cout << "Line [" << lineCount << "] No user was added. Default username is set: [" << user << "]" << std::endl;
	}
	if (this->password.empty())
	{
		this->password = "admin";
		std::cout << "Line [" << lineCount << "] No password was set for user: ["<< user << "]" << " default password is set." << std::endl;

	}

}

void	UsersAndPasswords::findUsersAndPasswords(std::vector<std::string> lines)
{
	size_t placeOfDelimiter;
	std::vector<std::string>::iterator x = lines.begin();

	for (; x != lines.end(); ++x)
	{
		++lineCount;
		if (checkLine(*x, &placeOfDelimiter))
		{
			this->user = setUser(*x, placeOfDelimiter);
			this->password = setPassword(*x, placeOfDelimiter);
			checkForEmpty();
			this->mapUsersAndPasswords.insert(std::make_pair(this->user, this->password));
		}
	}
}

std::map<std::string, std::string>	UsersAndPasswords::getUsersAndPasswords() const
{
	return this->mapUsersAndPasswords;
}