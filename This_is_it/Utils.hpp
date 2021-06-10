/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 10:29:59 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/10 10:37:07 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "Webserver.hpp"

bool		isEmptyLine(std::string &line);
std::string trimFrontOfString(std::string &line);
std::string trimFrontAndBackOfString(std::string &line);

#endif;
