/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freeArray.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:04 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/12 14:16:07 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	void	freeArray(char **array)
	{
		for (int i = 0; array[i]; ++i)
			free(array[i]);
		free(array);
	}
}
