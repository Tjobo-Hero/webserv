#include "Utils.hpp"

namespace Utils
{
	static std::string	setLocationPath(std::string &startLine, size_t start, size_t end)
	{
		return startLine.substr(start, end);;
	}

	static std::string	lookForWhitespaces(std::string &startLine, size_t pos_char, size_t pos_end, size_t pos_bracket, int lineCount)
	{
		size_t only_whitespaces = startLine.find_first_not_of(WHITESPACE, pos_end);
		if (only_whitespaces != pos_bracket)
			throw parseError("invalid path, character between path and '{' ", lineCount);
		return setLocationPath(startLine, pos_char, (pos_end - pos_char));
	}

	static std::string	lookForEnd(std::string &startLine, size_t pos_bracket, int lineCount)
	{
		size_t pos_char = startLine.find_first_of(startLine[0], 0);
		size_t pos_end = startLine.find_first_of(WHITESPACE, pos_char);
		if (pos_end == std::string::npos)
			return setLocationPath(startLine, pos_char, (pos_bracket - pos_char));
		return lookForWhitespaces(startLine, pos_char, pos_end, pos_bracket, lineCount);

	}

	static std::string	lookForBracket(std::string &startLine, int lineCount)
	{
		size_t pos_bracket = startLine.find_first_of("{", 0);
		if (pos_bracket == std::string::npos)
			throw parseError("missing bracket ", lineCount);
		return lookForEnd(startLine, pos_bracket, lineCount);
	}

	std::string	checkLocationPath(std::string &startLine, int lineCount)
	{
		startLine.erase(0, startLine.find_first_of(WHITESPACE, 0));
		Utils::removeSpacesBeforeAfter((&startLine));
		if ((startLine[0] == '*' && startLine[1] == '.') || startLine[0] == '/')
			return lookForBracket(startLine, lineCount);
		throw parseError("missing location path ", lineCount);
	}
}