/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:01 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/07/12 14:34:51 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONUTILS_HPP
# define CONNECTIONUTILS_HPP

#include "../Webserver.hpp"
# include <iostream>

namespace Utils
{
	long	getTime();
	void	signalHandler(int signal);
	void	freeArray(char **array);
	std::string base64_decode(std::string const& encoded_string);
	std::string createParameter(std::string configLine);
	bool		skipEmptyLine(std::string *line);
	void		removeSpacesBeforeAfter(std::string *line);
	std::string findFirstWord(std::string &line);

	std::string checkLocationPath(std::string &startLine, int lineCount);

void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine);

}
#endif