/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 15:17:33 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/11 15:41:44 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#define INVALID -1

#define BLANKS "\t\v "
int main ()
{
	std::vector<std::string> test(5);
	test[0] = "/robijn  {";
	
	std::string locationPath;

	size_t bracketPosition = test[0].find_first_of("{", 0);
	size_t forwardslashPosition = test[0].find_first_of("/", 0);
	size_t endoflocationPath = test[0].find_first_of(BLANKS, forwardslashPosition);
	size_t checkIfOnlyBlanksBetweenPathAndBracket = test[0].find_first_not_of(BLANKS, endoflocationPath);

	if (bracketPosition == std::string::npos || forwardslashPosition == std::string::npos)
		return INVALID;
	else if (endoflocationPath == std::string::npos) // no space between path and bracket
		locationPath = test[0].substr(forwardslashPosition, bracketPosition - forwardslashPosition);
	else if (checkIfOnlyBlanksBetweenPathAndBracket != bracketPosition)
		return INVALID;
	else
	{
		size_t lengthOfLocationPath = endoflocationPath - forwardslashPosition;
		locationPath = test[0].substr(forwardslashPosition, lengthOfLocationPath);
	}
	if (locationPath.back() != '/')
	{
		std::cout << "BACK PATH: " << locationPath.back() << std::endl;
		locationPath.append("/");
	}

	
	
		
	
	
	// if (forwardslashPosition == std::string::npos)
	// {
	// 	std::cout << "No forward slash" << std::endl;
	// 	return INVALID;
	// }
	// else if (spaceBetweenBracketAndEndOfPath != bracketPosition && (endoflocationPath + 1) != '{')
	// {
	// 	std::cout << "Something after path is invalid" << std::endl;
	// 	return INVALID;
	// }
	// else
	// {
	// 	locationPath = test[0].substr(forwardslashPosition, lengthOfPath);
	// }
	

	std::cout << "SUCCES" << std::endl;
	std::cout << locationPath << std::endl;
	std::cout << test[0] << std::endl;
	locationPath.assign(test[0].begin(), test[0].end());
	std::cout << test[0] << std::endl;
	
	return 0;
}

	// size_t end = delimiter > bracketPosition; // returns 0 if not true and 1 if true
	// if (delimiter > bracketPosition) // only one path was found before '{ : images {'
	// 	end = bracketPosition;
	// else if (fields[RIGHT].find_first_not_of(BLANKS, delimiter) == bracketPosition)
	// 	end = delimiter;
	// if (!end)
	// 	return INVALID;