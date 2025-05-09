




#ifndef		TOKEN_HPP
# define	TOKEN_HPP

# include <string>
# include "CountingStream.hpp"
# include "module.hpp"


// typedef int	BlockType;

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
	Block::type_e	_blockType;
	std::string		_word;
	std::size_t		_wordStartPos;
	CountingStream	_csFile;

	void 				skipWhiteSpaceAndComments(void);

public:
	// Token(void) {};
	Token(std::istream &file);

	void				setType(tokenType_e type);
	void				setBlock(Block::type_e blockType);

	tokenType_e			getType() const;
	Block::type_e		getBlock() const;
	const std::string	&getWord() const;
	size_t				getWordStartPos(void) const;
	size_t				getLine(void) const;

	void				nextToken(void);
};

#endif		// TOKEN_HPP
