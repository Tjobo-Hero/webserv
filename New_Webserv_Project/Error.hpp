/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Error.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/09 10:59:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/09 11:12:37 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include "Webserver.hpp"

class serverError : public std::exception {
	
	private:

	std::string _error;
	
	public: 

		serverError(const char *context, const char *message) : _error(std::string(context) + ":" + message) {
			return;
		}
		const char *what() const throw() {
			return _error.c_str();
		}
		virtual ~serverError() throw () {
			return;
		}
};

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
#endif