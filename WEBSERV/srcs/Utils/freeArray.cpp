/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freeArray.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:04 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/07 12:46:09 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionUtils.hpp"

namespace Utils
{
	void	freeArray(char **array)
	{
		for (int i = 0; array[i]; ++i)
			free(array[i]);
		free(array);
	}
}
