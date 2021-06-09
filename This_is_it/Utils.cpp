/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 14:59:49 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 15:25:31 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"

namespace Utils
{

bool	isEmptyLine(std::string &line)
{
	for (size_t i = 0; line[i]; ++i) {
		if (std::isspace(line[i]) == 0)
			return false;
	}
	return true;
}

std::string trimFrontOfString(std::string &line)
{
	std::string result;

	size_t i = 0;
	while (std::isspace(line[i]) && line[i] != std::string::npos)
		i++;
	while (!std::isspace(line[i]) && line[i] != std::string::npos)
	{
		result += line[i];
		i++
	}
	return (result);
}

std::string trimFrontAndBackOfString(std::string &line)
{
	size_t start = 0;
	size_t end;

	while (std::isspace(line[start]) && line[start] != std::string::npos)
		start++;
	end = line.length() - 1;
	while (std::isspace(line[end]) && line[end] != std::string::npos)
		end--;
	return line.substr(start, end + 1);
	
}

} // end of namespace UTILS
