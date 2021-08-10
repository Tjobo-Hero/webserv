/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 12:28:01 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/10 10:43:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONUTILS_HPP
# define CONNECTIONUTILS_HPP

# include "../Webserver.hpp"
# include <iostream>
# include <map>

template<typename T>
void	print(T &x)
{
	std::cout << x << std::endl;
}

namespace Utils
{
	long	getTime();
	void	signalHandler(int signal);
	void	freeArray(char **array);
	std::string base64_decode(std::string const& encoded_string);
	std::string createParameter(std::string configLine);
	bool		skipEmptyLine(std::string &line);
	void		removeSpacesBeforeAfter(std::string *line);
	std::string findFirstWord(std::string &line);
	std::string checkLocationPath(std::string &startLine, int lineCount);

	void		getKeyValue(const std::string &line, std::string &user, std::string &password, const char* delimiter, const char* endOfLine);
	void		getUserAndPassword(const std::vector<std::string> lines, std::string &user, std::string &password);

	std::map<int, std::string>	getLinesFromTextFile(std::fstream *configFile);
	void	deleteEmptyLines(std::map<int, std::string> &lines);
	void	removeComments(std::string &lines);
	void	deleteSpacesBeforeAndAfter(std::map<int, std::string> &lines);
	void	checkBrackets(std::map<int, std::string> lines);
	void	checkEndOfLineForSemicolon(std::map<int, std::string> lines);
	void	openTextFile(std::fstream &file, std::string income);
	void	closeTextFile(std::fstream &file);
	void	createSocket(long &socketFD, const std::string host);
	void	setDataStructureToZero(struct sockaddr_in &addr, const int portNumber);
	void	setSocketOption(long &socketFD, const std::string host);
	void	bindSocket(long &socketFD, struct sockaddr_in &addr, const std::string host);
	void	listenSocket(long &socketFD, const std::string host);
}
#endif