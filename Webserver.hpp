/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:58:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/23 11:30:43 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <fstream>
# include "ServerCluster.hpp"
# include "Request.hpp"
# include "CGI.hpp"
# include "Server.hpp"

class ServerCluster;

extern Connection *g_recentConnection;

#endif