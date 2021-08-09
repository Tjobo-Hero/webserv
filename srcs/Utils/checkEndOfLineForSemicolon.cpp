/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkEndOfLineForSemicolon.cpp                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 10:59:01 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/09 11:03:41 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	checkEndOfLineForSemicolon(std::map<int, std::string> lines)
	{
		std::map<int, std::string>::iterator it = lines.begin();
		for (; it != lines.end(); ++it)
		{
			if (*(it->second.rbegin()) != '{' && *(it->second.rbegin()) != '}')
				if (*(it->second.rbegin()) != ';')
					throw parseError("syntax error, line doesn't end with ';' ", it->first);
		}
	}
}