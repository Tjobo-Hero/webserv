/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConnectionUtils.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:04 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/21 09:36:18 by timvancitte   ########   odam.nl         */
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

void	signalHandler(int signal) {
	if (signal != SIGPIPE)
		std::cout << "How can this happen? SIGPIPE error" << std::endl;
	g_recentConnection->resetConnection();
	g_recentConnection->closeConnection();
}

void	freeArray(char **array) {

	for (int i = 0; array[i]; ++i) {
		free(array[i]);
	}
	free(array);
}

}