




#ifndef		CONFIG_PARSER_HPP
# define	CONFIG_PARSER_HPP

# include <fstream>
# include <vector>
# include "Token.hpp"

class	Parser {
private:
	Token			_token;
	std::size_t		_wordStartPos;

	void	parseBlock(void);
	void	parseDirective(void);
	void	handleDirective(const std::string &name, const std::vector<std::string> &args);
	void	handleBlockStart(const std::string &name, const std::vector<std::string> &args);
	void	handleBlockEnd(const std::string &name, const std::vector<std::string> &args);

public:
	// Parser(void);
	Parser(std::ifstream &file);

	void	parseConfigFile(void);

	/* Exception Classes */
	class	UnexpectedToken;
	class	ExpectedToken;
	class	Exception;
	class	DirectiveLength;
	class	LineLength;
	class	FileSize;
	class	EmptyBlock;
	class	HttpClosed;
	class	FirstBlock;
	class	SameBlock;
	class	WrongBlock;
	class	UnknownDirective;
};

# include "ParseException.hpp"


#endif		// CONFIG_PARSER_HPP
