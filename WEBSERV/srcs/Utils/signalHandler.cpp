/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signalHandler.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 09:57:54 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/07/07 11:49:45 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionUtils.hpp"

namespace Utils
{
	void	signalHandler(int signal)
	{
		if (signal != SIGPIPE)
			std::cout << "How can this happen? SIGPIPE error" << std::endl;
		g_recentConnection->resetConnection();
		g_recentConnection->closeConnection();
	}
}
