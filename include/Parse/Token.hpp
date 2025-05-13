




#ifndef		TOKEN_HPP
# define	TOKEN_HPP

# include <string>
# include "CountingStream.hpp"
# include "Module.hpp"

class	Token {
public:
	enum	type_e {
		EMPTY = 0,
		WORD,			// 64 char string len
		END_STATEMENT,	// ';'
		BEGIN_BLOCK,	// '{'
		END_BLOCK,		// '}'
		END_FILE,		// EOF
	};

private:
	type_e			_type;
	std::string		_word;
	std::size_t		_wordStartPos;
	CountingStream	_csFile;

	/* Member Functions */
	void 				skipWhiteSpaceAndComments(void);

public:
	/* Contsructor */
	Token(char *const path, std::istream &file);

	/* Member Functions */
	void				nextToken(void);

	/* Setters */
	void				setType(type_e type);

	/* Getters */
	type_e			getType(void) const;
	std::string		getWord(void) const;
	std::string		getPath(void) const;
	std::size_t		cursorLine(void) const;
	std::size_t		cursorPos(void) const;
	std::size_t		getWordStartPos(void) const;
};

#endif		// TOKEN_HPP
