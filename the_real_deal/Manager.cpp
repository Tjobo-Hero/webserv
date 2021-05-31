/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Manager.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 10:30:47 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/31 11:23:08 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"

Manager::Manager(void) : _config(DEFAULT_CONFIG)
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