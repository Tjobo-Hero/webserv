/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getTime.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 09:57:54 by rbraaksm      #+#    #+#                 */
/*   Updated: 2021/07/07 11:50:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionUtils.hpp"

namespace Utils
{
	long	getTime()
	{
		struct timeval currentTime;
		gettimeofday(&currentTime, NULL);
		return currentTime.tv_sec;
	}
}
