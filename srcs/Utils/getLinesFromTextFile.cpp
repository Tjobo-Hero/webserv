/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getLinesFromTextFile.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 12:40:59 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/07 15:31:44 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	std::map<int, std::string>	getLinesFromTextFile(std::fstream *configFile)
	{
		std::map<int, std::string>	tmp;
		std::string income;
		int i = 1;
		while (std::getline(*configFile, income))
		{
			removeComments(income);
			if (skipEmptyLine(income) == false)
				tmp.insert(std::pair<int, std::string>(i, income));
			++i;
		}
		return tmp;
	}
}