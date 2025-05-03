




#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include <fstream>
# include <vector>
#include "config_Token.hpp"

class	Parser {
private:
	Token			_token;
	std::size_t		_wordStartPos;

	void	parseBlock(void);
	void	parseDirective(void);
	void	handleDirective(std::string name, const std::vector<std::string> &args);
	void	handleBlockStart(std::string name, const std::vector<std::string> &args);
	void	handleBlockEnd(std::string name, const std::vector<std::string> &args);

public:
	Parser(std::ifstream &file);

	void	parseConfigFile(void);
};

#endif
