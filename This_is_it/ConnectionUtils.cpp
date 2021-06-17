/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConnectionUtils.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:04 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/17 12:31:58 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionUtils.hpp"

namespace Utils
{
	
long	getTime() {
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec;
}

}