/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: robijnvanhouts <robijnvanhouts@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/18 13:41:42 by robijnvanho   #+#    #+#                 */
/*   Updated: 2021/06/22 12:14:14 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Webserver.hpp"

void	free_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

long 	getTime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (currentTime.tv_sec);
}