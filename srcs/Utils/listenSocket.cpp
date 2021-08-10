/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listenSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:34:16 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/10 10:36:15 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	listenSocket(long &socketFD, const std::string host)
	{
		if (listen(socketFD, NR_OF_CONNECTIONS) < 0)
			throw startupError("to listen for server host: ", host);
	}
}