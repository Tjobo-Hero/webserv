/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Webserver.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 11:58:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 10:52:57 by robijnvanho   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <fstream>
# include "ServerCluster/ServerCluster.hpp"
# include "Request.hpp"
# include "CGI.hpp"
# include "Server.hpp"
# include "Connection.hpp"

class ServerCluster;
class Connection;

void	outputErrorMessageAndExitCode(const std::string &errorMessage, int exitCode);

void	outputErrorMessageAndExitCode(const std::string &errorMessage, int exitCode);

extern Connection *g_recentConnection;

#endif