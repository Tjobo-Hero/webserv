/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Manager.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:30:47 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 14:06:16 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"

Manager::Manager(void)
{
	return;
}

Manager::~Manager(void)
{
	return;
}
void	Manager::config(std::string config_file)
{
	_config.parse(config_file.c_str());
	return;
}