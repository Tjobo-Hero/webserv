/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Connection.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-hou <rvan-hou@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 10:44:17 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/08/30 13:42:04 by rvan-hou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
# define CONNECTION_HPP

#include "Libraries.hpp"

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
		bool					isChunked(size_t position) const;
		
		void		resetConnection();
		void		closeConnection();
		void		sendData(const size_t bodylen);
		void		sendNotChunked();
		void		sendHeader(size_t ret, const size_t headerlen);
		void		sendFilledChunks(size_t ret, const size_t bodylen, const size_t headerlen);
		std::string	createChunk(const size_t headerlen, size_t bytesToSend);
		void		sendEnd(size_t ret);
		std::string	receive();
		void		startReading();

		void		sendChunked(const size_t bodylen, const size_t headerlen);

		Response *myResponse;

};
#endif