/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Connection.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 10:44:17 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/17 14:02:06 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
# define CONNECTION_HPP

#include "Webserver.hpp"

class Response;
class Connection
{	
	private:

		unsigned long	_timeLastContactInSeconds;
		long			_acceptFD;
		size_t			_bodyBytesSent;
		std::string		_responseString;
		std::string		_acceptBuffer;
		bool			_hasFullRequest;
		bool			_headerSend;
		bool			isFullRequest() const;

	public:
		
		Connection(void);
		Connection(Connection const &src);
		~Connection(void);

		Connection&		operator=(Connection const &obj);

		void	setTimeLastRead(const unsigned long &time);
		void	setFD(const long &FD);
		void	setResponseString(const std::string &response);
		
		const unsigned long&	getTimeLastRead() const;
		const long&				getAcceptFD() const;
		const bool&				hasFullRequst() const;
		const std::string&		getBuffer() const; // Which buffer?
		const std::string&		getResponseString() const;
		
		void		resetConnection();
		void		closeConnection();
		void		sendData(const size_t bodylen);
		std::string	receive();
		void		startReading();

		void		sendChunked(const size_t bodylen, const size_t headerlen);

		Response *myResponse;

};
#endif