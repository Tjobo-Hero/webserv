/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tcpserver.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 14:57:08 by tvan-cit      #+#    #+#                 */
/*   Updated: 2021/05/17 16:12:53 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#include <string.h>

int main(int argc, char **argv)
{
	int						listenfd;
	int						connfd;
	int						n;
	struct	sockaddr_in		servaddr;
	uint8_t					buff[MAXLINE+1];
	uint8_t					recvline[MAXLINE+1];

	// Creating a socket. Basically a file you can read or write from/to
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("socket error.");
	
	// Accepting a connecting
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family			= AF_INET;
	servaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	servaddr.sin_port			= htons(SERVER_PORT); /*server port */

	// Once the address is set up where going to bind the socket 
	//  to the address

	if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		err_n_die("bind error.");

	if (listen(listenfd, 10)) < 0)
		err_n_die("listen error.");
	
	for ( ; ; )
	{
		struct	sockaddr_in	addr;
		socklen_t	addr_len;

		// accepts blocks until an incoming connection arrives
		// it returns a "file descripto" to the connection
		printf("waiting for a connection on port %d\n", SERVER_PORT);
		fflush(stdout);
		connfd = accept(listenfd, (SA *) NULL, NULL);

		// zero out the receive buffer to make sure it ends up NULL terminated
		memset(recvline, 0, MAXLINE);
		
		while ((n = read(connfd, recvline, MAXLINE-1)) > 0)
		{
			fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);
			
			// hacky way to detect the end of the message.
			if (recvline[n - 1] == '\n')
				break;
			memset(recvline, 0, MAXLINE);
		}
		if (n < 0)
			err_n_die("read error.");
		
		// now send a response
		snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK \r\n\r\n HELLO");

		// note: normally, you may want to check the results from write and close in 
		// case errors occur. For now. I'm ignoring them
		write(connfd, (char*)buff, strlen((char*)buff));
		close(connfd);
	}
}