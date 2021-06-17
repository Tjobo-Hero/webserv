/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConnectionUtils.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:01 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/17 14:46:56 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONUTILS_HPP
# define CONNECTIONUTILS_HPP

#include "Webserver.hpp"
namespace Utils
{
	long	getTime();
	void	signalHandler(int signal);
}
#endif