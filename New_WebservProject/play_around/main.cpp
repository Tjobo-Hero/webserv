/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 15:17:33 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 17:22:32 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#define BLANKS "\t\v "
int main ()
{
	std::vector<std::string> test(5);
	test[0] = "/robijn{";
	
	size_t bracket = test[0].find_first_of("{", 0);
	size_t delimiter = test[0].find_first_of(BLANKS, 0);

	std::cout << "bracket: " << bracket << std::endl;
	std::cout << "delimiter: " << delimiter << std::endl;
	size_t end = delimiter > bracket;

	if (delimiter == std::string::npos) // only one path was found before '{ : images {'
		end = bracket;
  	else if (test[0].find_first_not_of(BLANKS, delimiter) == bracket)
		end = delimiter;
	if (!end)
		return -1;

	std::cout << "end: "<< end << std::endl; 
	return 0;
}

	// size_t end = delimiter > bracketPosition; // returns 0 if not true and 1 if true
	// if (delimiter > bracketPosition) // only one path was found before '{ : images {'
	// 	end = bracketPosition;
	// else if (fields[RIGHT].find_first_not_of(BLANKS, delimiter) == bracketPosition)
	// 	end = delimiter;
	// if (!end)
	// 	return INVALID;