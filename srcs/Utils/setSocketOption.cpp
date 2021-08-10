/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setSocketOption.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:10:39 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/10 10:20:11 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	setSocketOption(long &socketFD, const std::string host)
	{
		int options = 1;
		if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEPORT, &options, sizeof(options)) < 0)
			throw startupError("to setsockopt for server with host: ", host);
	}

}