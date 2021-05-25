/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 10:42:44 by tvan-cit      #+#    #+#                 */
/*   Updated: 2021/05/17 10:47:31 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h> /*basic socket definitions */
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> /* for inet_pton, and the like */
#include <stdarg.h> /* for variable argument functions, like err_n_die */
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

//useful constants
#define	SERVER_PORT	18000

#define MAXLINE 4096
#define SA struct sockaddr

void	err_n_die(const char *fmt, ...);
char	*bin2hex(const unsigned char *input, size_t len);




#endif