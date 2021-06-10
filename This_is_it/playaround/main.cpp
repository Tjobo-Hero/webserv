/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:37:24 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/10 10:40:56 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
	std::string line = "#asdfasdf asdflaksdfl";
	
	if (std::find(line.begin(), line.end(), '#') == std::string::npos)
		std::cout << "yes" << std::endl;
	return 0;
}