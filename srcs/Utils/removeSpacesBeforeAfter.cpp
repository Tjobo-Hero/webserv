#include "Utils.hpp"

namespace Utils
{
	void	removeSpacesBeforeAfter(std::string *line)
	{
		size_t n = line->find_last_not_of(WHITESPACE);
		size_t x = line->find_first_not_of(WHITESPACE);
		if (n != std::string::npos)
			line->assign(line->substr(0, n + 1));
		if (x != std::string::npos)
			line->assign(line->substr(x));
	}
}