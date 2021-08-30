/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setSocketOption.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:10:39 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/30 10:33:23 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/* This helps in manipulating options for the socket referred by the file descriptor sockfd. This is completely optional,
but it helps in reuse of address and port. Prevents error such as: “address already in use”. */

namespace Utils
{
	void	setSocketOption(long &socketFD, const std::string host)
	{
		int options = 1;
		if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEPORT, &options, sizeof(options)) < 0)
			throw startupError("to setsockopt for server with host: ", host);
	}

}