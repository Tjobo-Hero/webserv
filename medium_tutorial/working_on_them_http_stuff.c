/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   working_on_them_http_stuff.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 12:05:06 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/05/20 12:39:44 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	
	int server_fd;
// Step 1. Create a socket
// A socket, server_fd, is created with the socket system call:
// int server_fd = socket(domain, type, protocol);

// domain: communication domain in which the socket should be created. 
// Some of address families are AF_INET (IP), AF_INET6 (IPv6), AF_UNIX 
// (local channel, similar to pipes), AF_ISO (ISO protocols), and AF_NS 
// (Xerox Network Systems protocols).
//
// type: type of service. This is selected according to the properties 
// required by the application: SOCK_STREAM (virtual circuit service),
// SOCK_DGRAM (datagram service), SOCK_RAW (direct IP service). 
// Check with your address family to see whether a particular service is available.
//
// protocol: communication domain in which the socket should be created. 
// Some of address families are AF_INET (IP), AF_INET6 (IPv6), AF_UNIX 
// (local channel, similar to pipes), AF_ISO (ISO protocols), and AF_NS 
//(Xerox Network Systems protocols).
//
// For TCP/IP sockets, we want to specify the IP address family 
// (AF_INET) and virtual circuit service (SOCK_STREAM). 
// Since there’s only one form of virtual circuit service, 
// there are no variations of the protocol, so the last argument, 
// protocol, is zero. Our code for creating a TCP socket looks like this:

if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
	perror("cannot create socket");
	return 0;
}

// Step 2. Identify (name) a socket
// When we talk about naming a socket, we are talking about assigning 
// a transport address to the socket (a port number in IP networking). 
// In sockets, this operation is called binding an address and the bind 
// system call is used for this.

// The analogy is that of assigning a phone number to the line that you requested 
// from the phone company in step 1 or that of assigning an address to a mailbox.

// The transport address is defined in a socket address structure. 
// Because sockets were designed to work with various different types 
// of communication interfaces, the interface is very general. Instead 
// of accepting, say, a port number as a parameter, it takes a sockaddr 
// structure whose actual format is determined on the address family 
// (type of network) you're using. For example, if you're using UNIX 
// domain sockets, bind actually creates a file in the file system.

// system call: int bind(int socket, const struct sockaddr *address, socklen_t address_len);
// 
// socket: is the socket that was created with the socket system call.
//
// sockaddr: For the second parameter, the structure sockaddr is a generic 
// container that just allows the OS to be able to read the first couple of 
// bytes that identify the address family. The address family determines what 
// variant of the sockaddr struct to use that contains elements that make sense 
// for that specific communication type. For IP networking, we use 
// struct sockaddr_in, which is defined in the header netinet/in.h. 
// This structure defines:
//
// struct sockaddr_in 
// { 
//     __uint8_t         sin_len; 
//     sa_family_t       sin_family; 
//     in_port_t         sin_port; 
//     struct in_addr    sin_addr; 
//     char              sin_zero[8]; 
// };

// Before calling bind, we need to fill out this structure. 
// The three key parts we need to set are:
// 
// sin_family: The address family we used when we set up the socket. 
// In our case, it’s AF_INET.
//
// sin_port: The port number (the transport address). 
// You can explicitly assign a transport address (port) or 
// allow the operating system to assign one. If you’re a client 
// and won’t be receiving incoming connections, you’ll usually 
// just let the operating system pick any available port number 
// by specifying port 0. If you’re a server, you’ll generally 
// pick a specific number since clients will need to know a 
// port number to connect to.
//
// sin_addr: The address for this socket. This is just your 
// machine’s IP address. With IP, your machine will have one IP 
// address for each network interface. For example, if your machine 
// has both Wi-Fi and ethernet connections, that machine will have 
// two addresses, one for each interface. Most of the time, we don’t 
// care to specify a specific interface and can let the operating 
// system use whatever it wants. The special address for this is 0.0.0.0, 
// defined by the symbolic constant INADDR_ANY.
// Since the address structure may differ based on the type of 
// transport used, the third parameter specifies the length of that structure. 
// This is simply sizeof(struct sockaddr_in).

// The code to bind a socket looks like this:

struct sockaddr_in address;
const int PORT = 8080; // Where the cleints can reach at

/*htonl converts a long integer (e.g. address)to a network representation */
/*htons converts a short integer (e.g. port) to a network representation */

memset((char*)&address, 0, sizeof(address)); // Set every variable in the struct to zero. 
address.sin_family = AF_INET;
address.sin_addr.s_addr = htonl(INADDR_ANY);
address.sin_port = htons(PORT);

if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
{
	perror("bind failed");
	return 0;
}

// Step 3. On the server wait for an incoming connection
//
// Before a client can connect to a server, the server 
// should have a socket that is prepared to accept the connections. 
// The listen system call tells a socket that it should be capable 
// of accepting incoming connections:
//
// int listen(int socket, int backlog)
// 
// backlog: defines the maximum number of pending connections that 
// can be queued up before connections are refused.
//
// accept: system call grabs the first connection request 
// on the queue of pending connections (set up in listen) and 
// creates a new socket for that connection.
//
// The original socket that was set up for listening 
// is used only for accepting connections, not for exchanging 
// data. By default, socket operations are synchronous, or blocking, 
// and accept will block until a connection is present on the queue.
// 
}