#include "Utils.hpp"

namespace Utils
{
	std::string findFirstWord(std::string &line)
	{
		size_t		start;
		size_t		end;

		start = line.find_first_not_of(WHITESPACE, 0);
		end = line.find_first_of(WHITESPACE, start);
		return line.substr(start, end);
	}
}