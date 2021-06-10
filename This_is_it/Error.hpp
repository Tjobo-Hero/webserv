/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Error.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:13:43 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/10 15:07:03 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include "Webserver.hpp"

// void	errMsgAndExit(const std::string &errMsg, int code)
// {
// 	std::cerr << "error: " << errMsg << std::endl;
// 	exit(code);
// }

class parseError : public std::exception {
		public:
			parseError(std::string line, size_t lineCount) 
				: _error(std::string(line) + ": syntax error line " + std::to_string(lineCount) + "\n") {
			}
			parseError(std::string line, const char *message) 
				: _error("Error: line:" + std::string(line) + ": " + message) {
			}
			const char *what() const throw() {
				return _error.c_str();
			}
			virtual ~parseError() throw() {}
		private:
			std::string _error;
};

class openFileError : public std::exception 
{
		public:
			openFileError(const char *message, const char *configPath) 
				: _error(message + std::string(configPath)) {
			}
			const char *what() const throw() {
				return _error.c_str();
			}
			virtual ~openFileError() throw() {}
		private:
			std::string _error;
};

#endif