/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 09:39:47 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/10 09:44:49 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	createSocket(long &socketFD, const std::string host)
	{
		socketFD = socket(PF_INET, SOCK_STREAM, 0);
		if (socketFD < 0 )
			throw startupError("to create socket for server with host: ", host);
	}
}