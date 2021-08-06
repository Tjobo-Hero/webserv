/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkBrackets.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 15:43:21 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/06 16:03:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	checkBrackets(std::map<int, std::string> lines)
	{

		std::map<int, std::string>::iterator it = lines.begin();
		size_t open = 0;
		size_t closed = 0;

		for (; it != lines.end(); ++it)
		{
			open += std::count(it->second.begin(), it->second.end(), '{');
			closed += std::count(it->second.begin(), it->second.end(), '}');
			if (open < closed)
				throw parseError("Brackets aren't open ", it->first);
		}
		--it;
		if (open > closed)
			throw parseError("Brackets aren't closed ", it->first);
	}

}