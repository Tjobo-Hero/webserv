/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getLinesFromTextFile.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 12:40:59 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/06 16:34:03 by rbraaksm      ########   odam.nl         */
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
			tmp.insert(std::pair<int, std::string>(i, income));
			++i;
		}
		return tmp;
	}
}