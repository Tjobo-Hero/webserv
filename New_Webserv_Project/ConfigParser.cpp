/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigParser.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: timvancitters <timvancitters@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/07 10:50:00 by timvancitte   #+#    #+#                 */
/*   Updated: 2021/06/08 13:30:48 by timvancitte   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

ConfigParser::ConfigParser(){
	return;
}

ConfigParser::ConfigParser(ConfigParser const &src)
{
	if (this != &src)
		*this = src;
}

ConfigParser::~ConfigParser(){
	return;
}

ConfigParser&		ConfigParser::operator=(ConfigParser const &obj)
{
	if (this != &obj)
		std::cout << "HOI" <<std::endl;
	return *this;
}

int				ConfigParser::openConfigFile(const char* configFilePath)
{
	int						configFileFD;
	
	if ((configFileFD = open(configFilePath, O_RDONLY)) < 0) {
		throw ConfigParser::NotAValidFileException();
	}
	return configFileFD;
}

void			ConfigParser::sampleLine(std::string &line, fields &fields)
{
	if (line.empty())
		return; // Already checked before we go into the function, really necessary to do again?
	size_t	start = line.find_first_not_of(BLANKS, 0);
	if (start == std::string::npos)
	{
		fields[LEFT].clear();
		fields[RIGHT].clear();
		return;
	}
	size_t end = line.find_first_of(BLANKS, start);
	fields[LEFT] = line.substr(start, end);
	if (line.size() == 1) // incase we have '{' or '}'
		fields[RIGHT].clear();
	else
		fields[RIGHT] = std::string(line.begin() + line.find_first_not_of(BLANKS, end), line.end());
}

void			ConfigParser::convertTokens(configTokens &tokens, Server::allServers &_allServers)
{
	ServerConfiguration configuration;
	bool duplicate;
	
	while(!tokens.empty()) {
		configuration = tokens.front();
		
	}
}

void			ConfigParser::parseTheConfigFile(const char* configFilePath, Server::allServers &_allServers)
{
	fields fields(2);
	configTokens	tokens;
	int blockIndicator = MAIN_BLOCK;
	size_t lineCount = 0;
	std::string line;
	(void)_allServers;
	
	int configFileFD = openConfigFile(configFilePath);
	// if (configFileFD == -1)
	while (ft::getNextLine(configFileFD, line) > 0) {
		line.erase(0, line.find_first_not_of(BLANKS, 0)); // remove blanks before first field
		line.erase(std::find(line.begin(), line.end(), '#'), line.end()); // remove comments
		if (!line.empty()) {
			sampleLine(line, fields);
			// std::cout << "LEFT: [" << fields[LEFT] << "] RIGHT: [" << fields[RIGHT] << "]" << std::endl; 
			if ((blockIndicator = parseTheBlock(blockIndicator, fields, tokens)) == INVALID){
				std::cout << "Error at line: " << lineCount << std::endl;
				//TODO put a valid Throw error
			}
			++lineCount;
		}
	}
	if (close(configFileFD) == -1)
	{
		std::cout << "close file failed" << std::endl;
		// TODO throw error
	}
	if (tokens.empty())
	{
		std::cout << "no tokens in file" << std::endl;
		//TODO Throw error 
	}
	convertTokens(tokens, _allServers);

}

int		ConfigParser::addNewServerBlock(fields &fields, configTokens &tokens)
{
	if (fields[RIGHT].empty() || fields[RIGHT][0] != '{')
		return INVALID;
	tokens.push(ServerConfiguration()); // add a new server block
	fields[LEFT].assign(fields[RIGHT].begin() + 1, fields[RIGHT].end()); // geen idee 
	return SERVER_BLOCK;
}

// location /images {
int		ConfigParser::addNewRouteBlock(fields &fields, configTokens &tokens)
{
	std::string locationPath;

	size_t bracketPosition = fields[RIGHT].find_first_of("{", 0);
	size_t forwardslashPosition = fields[RIGHT].find_first_of("/", 0);
	size_t endoflocationPath = fields[RIGHT].find_first_of(BLANKS, forwardslashPosition);
	size_t spaceBetweenBracketAndEndOfPath = fields[RIGHT].find_first_not_of(BLANKS, endoflocationPath);

	if (bracketPosition == std::string::npos || forwardslashPosition == std::string::npos)
	{
		std::cout << "invalid path" << std::endl;
		return INVALID;
	}
	else if (endoflocationPath == std::string::npos) // no space between path and bracket
		locationPath = fields[RIGHT].substr(forwardslashPosition, bracketPosition - forwardslashPosition);
	else if (spaceBetweenBracketAndEndOfPath != bracketPosition)
	{
		std::cout << "invalid path" << std::endl;
		return INVALID;
	}
	else
	{
		size_t lengthOfPath = endoflocationPath - forwardslashPosition;
		locationPath = fields[RIGHT].substr(forwardslashPosition, lengthOfPath);
	}
	ServerConfiguration &currentServer = tokens.back();
	if (locationPath.back() != '/')
		locationPath.append("/");
	currentServer._allroutes[locationPath] = ServerConfiguration::directives();
	currentServer._routeIndex.push_back(locationPath);
	// TODO: add check to see if a route with the same path already exists
	if (!fields[RIGHT].empty())
		fields[LEFT].assign(fields[RIGHT].begin() + bracketPosition + 1, fields[RIGHT].end()); // TODO: checken of dit werkt want ik heb de functie hierboven herschreven
	return ROUTE_BLOCK;
}

int		ConfigParser::addNewBlock(fields &fields, configTokens &tokens, int blockIndicator)
{
	if (blockIndicator == MAIN_BLOCK)
		return addNewServerBlock(fields, tokens);
	else if (blockIndicator == SERVER_BLOCK)
		return addNewRouteBlock(fields, tokens);
	else
		return INVALID;
}
int		ConfigParser::addServerDirective(fields &fields, configTokens &tokens)
{
	size_t parameterEnd = fields[RIGHT].find_first_of(";", 0);
	if (parameterEnd == std::string::npos) // no ";" at the end of parameter
		return INVALID;
	std::string const &directiveName = fields[LEFT];
	if (directiveName == "error_page") {
		tokens.back()._errorPages.push_back(fields[RIGHT].substr(0, parameterEnd)); // pushing to error pages vector
	}
	else {
		tokens.back()._directives[fields[LEFT]] = fields[RIGHT].substr(0, parameterEnd); // pushing to directives map
	}
	if (!fields[RIGHT].empty()) // shift fields if we didn't reach End of File
		fields[LEFT].assign(fields[RIGHT].begin() + parameterEnd + 1, fields[RIGHT].end());
	return SUCCESS;
}

int		ConfigParser::addRouteDirective(fields &fields, configTokens &tokens)
{
	size_t parameterEnd = fields[RIGHT].find_first_of(";", 0);
	if (parameterEnd == std::string::npos) // no ";" at the end of parameter
		return INVALID;
	ServerConfiguration &currentServer = tokens.back();
	std::string &currentRoute = currentServer._routeIndex.back();
	currentServer._allroutes[currentRoute][fields[LEFT]] = fields[RIGHT].substr(0, parameterEnd);
	if (!fields[RIGHT].empty())
		fields[LEFT].assign(fields[RIGHT].begin() + parameterEnd + 1, fields[RIGHT].end());
	return SUCCESS;
}

int		ConfigParser::addNewDirective(fields &fields, configTokens &tokens, int blockIndicator)
{
	if (blockIndicator == SERVER_BLOCK)
		return addServerDirective(fields, tokens);
	else if (blockIndicator == ROUTE_BLOCK)
		return addRouteDirective(fields, tokens);
	else
		return INVALID;
}

int		ConfigParser::parseTheBlock(int blockIndicator, fields &fields, configTokens tokens)
{
	int		updatedBlockIndicator = blockIndicator;
	const char	**directive;

	if (fields[LEFT].empty())
		return blockIndicator;
	if (blockIndicator < ROUTE_BLOCK && fields[LEFT] == blockTypes[blockIndicator])
		updatedBlockIndicator = addNewBlock(fields, tokens, blockIndicator);
	else if (fields[LEFT][0] == '}')
	{
		updatedBlockIndicator -= 1; // change to parrent Block
		fields[RIGHT].erase(fields[LEFT].begin()); // skip the closing bracket
		if (fields[LEFT].empty()) { // shift fields if necessary
			fields[LEFT] = fields[RIGHT];
		}
	}
	else { // check if valid directive depening on Block
		directive = std::find(allDirectivesString[blockIndicator], \
		&allDirectivesString[blockIndicator][hashLen[blockIndicator] -1], \
		fields[LEFT]);
		if (!*directive || addNewDirective(fields, tokens, blockIndicator) == INVALID) {
			return INVALID;
		}
	}
	if (updatedBlockIndicator == INVALID || fields[LEFT].empty()) // reached end of file
		return updatedBlockIndicator;
	// did not reach end of file so we need to resample
	// fields[LEFT] is the new line, updated in the add_directive
	std::string swap = fields[LEFT];
	sampleLine(swap, fields);
	return parseTheBlock(updatedBlockIndicator, fields, tokens);
}

const char	*ConfigParser::NotAValidFileException::what() const throw()
{
	std::perror("Failed to open file: ");
	return NULL;
}
