/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removeComments.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 13:35:58 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/06 15:10:13 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	removeComments(std::string &line)
	{
		line.erase(std::find(line.begin(), line.end(), '#'), line.end());
	}
}