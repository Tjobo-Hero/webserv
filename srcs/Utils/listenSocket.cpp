/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listenSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:34:16 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/30 10:34:45 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

/* It puts the server socket in a passive mode, where it waits for the client to approach
the server to make a connection. The backlog, defines the maximum length to which the queue of
pending connections for sockfd may grow. If a connection request arrives when the queue is full,
the client may receive an error with an indication of ECONNREFUSED. */

namespace Utils
{
	void	listenSocket(long &socketFD, const std::string host)
	{
		if (listen(socketFD, NR_OF_CONNECTIONS) < 0)
			throw startupError("to listen for server host: ", host);
	}
}