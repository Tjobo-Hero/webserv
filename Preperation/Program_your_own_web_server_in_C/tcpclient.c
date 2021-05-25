/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tcpclient.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:55:44 by tvan-cit      #+#    #+#                 */
/*   Updated: 2021/05/17 10:33:29 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h> /*basic socket definitions */
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h> /* for variadic funtions */
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

// standard HTTP port
#define SERVER_PORT	80

#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main(int argc, char **argv)
{
	// local variables
	int		sockfd;
	int		n;
	int		sendbytes;
	struct	sockaddr_in	servaddr;
	char	sendline[MAXLINE];
	char	recvline[MAXLINE];

	// usage check
	if (argc != 2)
		err_n_die("usage: %s <server address>", argv[0]);
	
	// create a socket
	// AF_INET = Address Family - Internet
	// Two different types of sockets 1. stream socket (as see below) 
	// 2. datagram sockets
	// The '0' argument is to specify the protocol 0 == use TCP
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("Error while creating the socket!");

	// zero out the address
	// htons = Host to network, short. If you have two different computers talking to 
	// each other and the have different byte order they will still be able to talk to
	// each other using htons. 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(SERVER_PORT); /* chat server */

	// Convert address: convert the string representation of the ip address "1.2.3.4"
	// into a binary representation of the address "1.2.3.4" => "[1,2,3,4]"
	// inet_pton function converts a text representation of ip address to a 
	// binary equivalent 
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_n_die("inet_pton error for %s", argv[1]);
	
	// connect to the server
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_n_die("connect failed!");
	
	// If connecting doesn't fail it means that we're now connected 
	// Preparing mesage
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
	sendbytes = strlen(sendline);

	// Send the request -- making sure you send it all
	// This code is a bit fragile, since it bails if only some the bytes are sent.
	// Normally, you would want to retry, unless the return value was -1.
	if (write(sockfd, sendline, sendbytes) != sendbytes)
		err_n_die("write error");
	
	
	// Now read the server's response
	while ((n = read(sockfd, recvline, MAXLINE-1)) > 0)
	{
		printf("%s", recvline);
		// Zeroinig out the receive line after the print
		memset(recvline, 0, MAXLINE);
	}
	if (n < 0)
		err_n_die("read error");
	
	exit(0); // end succesfully
}

void	err_n_die(const char *fmt, ...)
{
	int errno_save;
	va_list		ap;

	// any system or library call can set errno, so we need 
	// to save it now
	
	errno_save = errno;

	// print out the fmt+args to standard out
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
	fflush(stdout);

	// print out error message if errno was set
	if (errno_save != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);	
	}
	va_end(ap);
	
	// this is the ..and_die part. Terminate with an error.
	exit(1);
}