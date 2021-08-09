/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deleteEmptyLines.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 13:06:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/07 14:47:13 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void deleteEmptyLines(std::map<int, std::string> &lines)
	{
		std::string	line;

		std::map<int, std::string>::iterator it = lines.begin();
		for (; it != lines.end(); ++it)
		{
			line = it->second;
			removeComments(it->second);
			if (Utils::skipEmptyLine(it->second) == true)
				lines.erase(it);
		}
	}
}