




#ifndef		CONFIG_PARSER_HPP
# define	CONFIG_PARSER_HPP

# include <fstream>
# include <vector>
# include "Token.hpp"
# include "Module.hpp"

class	Parser {
private:
	Token			_token;
	Block::Module	_innerBlock;
	std::size_t		_wordStartPos;

	/* Member Functions */
	void	parseBlock(void);
	void	parseDirective(void);
	void	collectArgs(std::vector<std::string> &args);
	void	handleDirective(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args);
	void	handleBlockStart(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args);
	void	handleBlockEnd(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args);

public:
	/* Contsructor */
	Parser(void);

	/* Member Functions */
	void	parseConfigFile(void);

	/* Exception Classes */
	class	Exception;
	/* Parser Size Limits */
	class	DirectiveLength;
	class	LineLength;
	class	FileSize;
	/* Parser Tokens */
	class	ExpectedToken;
	/* Block */
	class	WrongBlock;
	class	WrongArgs;
};

# include "ParseException.hpp"


#endif		// CONFIG_PARSER_HPP
