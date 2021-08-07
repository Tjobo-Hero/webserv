/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deleteSpacesBeforeAndAfter.cpp                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 15:12:57 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/06 15:14:39 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	deleteSpacesBeforeAndAfter(std::map<int, std::string> &lines)
	{
		std::map<int, std::string>::iterator it = lines.begin();
		for (; it != lines.end(); ++it)
			removeSpacesBeforeAfter(&it->second);
	}
}