/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerConfiguration.hpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 11:21:01 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 12:32:55 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONFIGURATION_HPP
# define SERVERCONFIGURATION_HPP

#include "Webserver.hpp"

class ServerConfiguration
{
	private:

	struct	_comparePrefix{
		//some opti required for subsequent // and location that ends with /
		_comparePrefix() {};
		bool	operator()(std::string const &lhs, std::string const &rhs) const {
			size_t	lhs_prefixes = 0;
			size_t	rhs_prefixes = 0;
			size_t	index = 0;

			while ((index = lhs.find('/', index)) != std::string::npos) {
				++index;
				++lhs_prefixes;
			}
			index = 0;
			while ((index = rhs.find('/', index)) != std::string::npos) {
				++index;
				++rhs_prefixes;
			}
			return (lhs_prefixes > rhs_prefixes
					|| (lhs_prefixes == rhs_prefixes && lhs > rhs));
		}
	};
	
	public:
	
	typedef std::map<std::string, std::string>		directives;
	typedef std::map<std::string, directives, _comparePrefix>	allRoutes;
	typedef std::vector<std::string>	errorPages;
	typedef allRoutes::value_type	singleRoute;
	typedef allRoutes::key_type routeIndex;

	//TODO check if varia
	
	ServerConfiguration(void);
	ServerConfiguration(ServerConfiguration const &src);
	~ServerConfiguration(void);
	

	ServerConfiguration&		operator=(ServerConfiguration const &obj);

	// private:

	directives 	_directives;
	allRoutes	_allroutes;
	errorPages	_errorPages;
	std::vector<routeIndex> _routeIndex;
};
#endif