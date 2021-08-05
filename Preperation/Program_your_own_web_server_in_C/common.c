/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 10:47:52 by tvan-cit      #+#    #+#                 */
/*   Updated: 2021/05/17 16:14:23 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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

char	*bin2hex(const unsigned char *input, size_t len)
{
	char *result;
	char *hexits = "0123456789ABCDEF";

	if (input == NULL || len <= 0)
		return NULL;
	
	// (2 hexits+space)/chr + NULL
	int resultlength = (len * 3) + 1;
	result = malloc(resultlength);
	bzero(result, resultlength);

	for (int i = 0; i < len; ++i)
	{
		result[i * 3]		= hexits[input[i] >> 4];
		result[(i * 3) + 1] = hexits[input[i] & 0x0F];
		result[(i * 3) + 2] = ' '; // for readability
	}
	
	return result;
}