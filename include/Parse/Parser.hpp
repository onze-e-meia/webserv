




#ifndef		CONFIG_PARSER_HPP
# define	CONFIG_PARSER_HPP

# include <fstream>
# include <vector>
# include "Token.hpp"

class	Parser {
private:
	Token			_token;
	Block::Module	_innerBlock;
	std::size_t		_wordStartPos;

	/* Member Functions */
	void	parseBlock(void);
	void	parseDirective(void);
	void	handleDirective(const std::string &name, const std::vector<std::string> &args);
	void	handleBlockStart(const std::string &name, const std::vector<std::string> &args);
	void	handleBlockEnd(const std::string &name, const std::vector<std::string> &args);

public:
	/* Contsructor */
	Parser(void);

	/* Member Functions */
	void	parseConfigFile(void);

	/* Exception Classes */
	class	SizeLimitError;

	class	Exception;

	class	DirectiveLength;
	class	LineLength;
	class	FileSize;

	class	UnexpectedToken;
	class	ExpectedToken;

	class	HttpClosed;
	class	FirstBlock;
	class	WrongBlock;
	class	WrongArgs;
};

# include "ParseException.hpp"


#endif		// CONFIG_PARSER_HPP
