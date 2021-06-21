/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:19:15 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/21 15:07:31 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(Request &request, Server &server) : _useCGI(request.getCGI()), _body(request.getBody()), _status(request.getStatus()), _contentType(request.getContentType()), _method(request.getMethod()), _fileFD(-1), _isFinished(false) {
	getPath path*(server, request, *this);

	
}