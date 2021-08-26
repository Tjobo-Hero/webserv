/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bindSocket.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 10:20:32 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/13 12:26:20 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	bindSocket(long &socketFD, struct sockaddr_in &addr, const std::string host)
	{
		if (bind(socketFD, (sockaddr*)&(addr), sizeof(addr)) < 0)
			throw startupError("to bind for server with host: ", host);
	}
}