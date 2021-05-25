# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: timvancitters <timvancitters@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/18 10:10:19 by timvancitte   #+#    #+#                  #
#    Updated: 2021/05/18 10:12:59 by timvancitte   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC=clang

CFLAGS=-g
COMMON_OBJS= common.o

all: $(COMMON_OBJS) tcpc tcps

# Common wrappers and definitions that all of the other examples use


tcpc: tcpclient.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcps tcpserver.c $(COMMON_OBJS)

tcps: tcpserver.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcps tcpserver.c $(COMMON_OBJS)
	

clean: 
	rm -rf *.o *.dSYM tcpc tcps