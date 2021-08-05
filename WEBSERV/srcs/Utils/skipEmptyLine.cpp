#include "Utils.hpp"

namespace Utils
{
	bool	skipEmptyLine(std::string *line)
	{
		size_t start = line->find_first_not_of(WHITESPACE, 0);
		return (start == std::string::npos) ? true : false;

	}
}