




#ifndef		CONFIG_PARSER_HPP
# define	CONFIG_PARSER_HPP

# include <fstream>
# include <vector>
# include "Token.hpp"
# include "Module.hpp"

/* Parser MAX limits */
# define MAX_DIRECTIVE_LEN	128
# define MAX_LINE_LEN		4096
# define MAX_FILE_SIZE		1024 * 1024 // 1 MiB

typedef const std::string				C_Str;
typedef const std::vector<std::string>	C_VecStr;

class	Parser {
private:
	Token			_token;
	Block::Module	_innerBlock;
	std::size_t		_wordStartPos;

	/* Member Functions */
	void	parseBlock(void);
	void	parseDirective(void);
	void	collectArgs(std::vector<std::string> &args);
	void	handleDirective(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args);
	void	handleBlockStart(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args);
	void	handleBlockEnd(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args);

public:
	/* Contsructor & Destructor */
	Parser(void);
	~Parser(void);

	/* Getters */
	Token			getToken(void) const;
	Block::Module	getInnerBlock(void) const;
	std::size_t		getWordStartPos(void) const;

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
