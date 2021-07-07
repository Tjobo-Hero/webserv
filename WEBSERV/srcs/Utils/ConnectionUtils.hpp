/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConnectionUtils.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:01 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/07 11:50:36 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONUTILS_HPP
# define CONNECTIONUTILS_HPP

#include "../Webserver.hpp"

namespace Utils
{
	long	getTime();
	void	signalHandler(int signal);
	void	freeArray(char **array);
	std::string base64_decode(std::string const& encoded_string);
}
#endif