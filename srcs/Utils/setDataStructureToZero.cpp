/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setDataStructureToZero.cpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/10 09:58:06 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/08/10 10:02:08 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	setDataStructureToZero(struct sockaddr_in &addr, const int portNumber)
	{
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(portNumber);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
}