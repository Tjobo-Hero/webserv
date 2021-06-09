/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Error.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 12:13:43 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 13:03:17 by timvancitte   ########   odam.nl         */
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
			parseError(const char *path, size_t lineCount) 
				: _error(std::string(path) + ": syntax error line " + std::to_string(lineCount) + "\n") {
			}
			parseError(const char *path, const char *message) 
				: _error(std::string(path) + ": " + message) {
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