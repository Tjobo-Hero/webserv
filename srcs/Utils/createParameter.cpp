#include "Utils.hpp"

namespace Utils
{
	std::string	createParameter(std::string configLine)
	{
		std::string ret;
		configLine.resize(configLine.size() - 1);
		ret = configLine.substr(configLine.find_first_of(WHITESPACE, 0));
		Utils::removeSpacesBeforeAfter(&ret);
		return (ret);
	}
}