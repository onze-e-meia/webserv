

#ifndef CONFIG_TOKE_HPP
# define CONFIG_TOKE_HPP

# include <string>
# include <fstream>
# include "CountingStream.hpp"

# define DIRECTIVE_LEN 64

typedef int	BlockType;

class	Token {
public:
	enum	tokenType_e {
		EMPTY = 0,
		WORD,			// 64 char string len
		END_STATEMENT,	// ';'
		BEGIN_BLOCK,	// '{'
		END_BLOCK,		// '}'
		END_FILE,		// EOF
	};

private:
	tokenType_e		_tokenType;
	BlockType		_blockType;
	std::string		_word;
	std::size_t		_wordStartPos;
	CountingStream	_file;

	void 				skipWhiteSpaceAndComments(void);

public:
	Token(std::ifstream &file);

	void				setType(tokenType_e type);
	void				setBlock(BlockType blockType);

	tokenType_e			getType() const;
	BlockType			getBlock() const;
	const std::string	&getWord() const;
	size_t				getWordStartPos(void) const;
	size_t				getLine(void) const;

	void				nextToken(void);
};

#endif
