/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bindSocket.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:20:32 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/30 10:33:58 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/* After creation of the socket, bind function binds the socket to the address and port number specified in addr(custom data structure).
In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address. */

namespace Utils
{
	void	bindSocket(long &socketFD, struct sockaddr_in &addr, const std::string host)
	{
		if (bind(socketFD, (sockaddr*)&(addr), sizeof(addr)) < 0)
			throw startupError("to bind for server with host: ", host);
	}
}