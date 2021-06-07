/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigUtils.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/01 14:18:26 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/07 15:06:09 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigUtils.hpp"


namespace ft 
{
	

bool	isDigitString(const std::string &str)
{
	if (str.find_first_not_of("0123456789") == std::string::npos)
		return true;
	else
		return false;
}

static long int	convert(const char *str, int i,
unsigned long int result, int sign)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result >= 922337203685477580 && (str[i] - '0') > 7) && sign == 1)
			return (-1);
		else if ((result >= 922337203685477580 && (str[i] - '0') > 8)
		&& sign == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int				atoi(const char *str)
{
	unsigned long int	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == ' ' || (8 < str[i] && str[i] < 14)))
		i++;
	if ((str[i] == '+' && str[i + 1] == '-') ||
	(str[i] == '-' && str[i + 1] == '+'))
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
		if (str[i] == '+')
			return (0);
	}
	result = convert(str, i, result, sign);
	return ((int)result * sign);
}

unsigned int	strToIp(std::string strIp) {
	size_t  sep = 0;
	unsigned int   n;
	unsigned char  m[4];
	size_t  start = 0;
	if (strIp == "localhost")
		strIp = "127.0.0.1";
	for (unsigned int i = 3 ; i != std::numeric_limits<uint32_t>::max(); i--) {
		sep = strIp.find_first_of('.', sep);
		std::string str = strIp.substr(start, sep);
		n = atoi(str.c_str());
		m[i] = static_cast<unsigned char>(n);
		sep++;
		start = sep;
	}
	unsigned final = *(reinterpret_cast<unsigned int *>(m));
	return final;
}

int	getNextLine(int fd, std::string& line)  { // lol
		static char readBuffer[READ_BUF_SIZE + 1];
		static std::string saved;
		size_t	found = saved.find('\n', 0);
		static ssize_t	bytesRead = -1;

		if (found != std::string::npos || !bytesRead) {
			line.clear();
			line = saved.substr(0, found);
			saved.erase(0, found + 1);
			if (!bytesRead) {
				bytesRead = -1;
				return 0;
			}
			return 1;
		}
		std::fill(readBuffer, readBuffer + sizeof(readBuffer), 0);
		while ((bytesRead = read(fd, readBuffer, READ_BUF_SIZE)) > 0) {
			saved.append(readBuffer);
			std::fill(readBuffer, readBuffer + sizeof(readBuffer), 0);
			found = saved.find('\n', 0);
			if (found != std::string::npos) {
				line.clear();
				line = saved.substr(0, found);
				saved.erase(0, found + 1);
				return 1;
			}
		}
		if (bytesRead == -1)
			std::cout << "Error: getNextLine" << std::endl; // MAKE REAL THROW
			// throw serverError("getNextLine: read:", strerror(errno));
		return getNextLine(fd, line);
}

} // end of namespace FT