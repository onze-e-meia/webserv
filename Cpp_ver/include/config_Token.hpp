

#ifndef CONFIG_TOKE_HPP
# define CONFIG_TOKE_HPP

// # include <iostream>
# include <string>
# include <fstream>
// # include <vector>
// # include <cctype>

# include <bitset>
# include "module_def.hpp"

# define DIRECTIVE_LEN 64;

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
	BlockType		_blockType;
	tokenType_e		_tokenType;
	std::string		_word;
	std::ifstream	&_file;
	int				_pos;
	int				_line;

public:
	Token(std::ifstream	&file);
	Token(const Token &other);

	void				setType(tokenType_e type);
	void				setBlock(BlockType flags);

	tokenType_e			getType() const;
	BlockType			getBlock() const;
	const std::string	&getWord() const;

	void				nextToken(void) {
		skipWhiteSpaceAndComments();
		_word.clear();
		char	ch = _file.get();
		if (ch == EOF)
			return (setType(END_FILE));
		else if (ch == '{')
			return (setType(BEGIN_BLOCK));
		else if (ch == '}')
			return (setType(END_BLOCK));
		else if (ch == ';')
			return (setType(END_STATEMENT));


		// NEED TO CHECK FOR '#' HERE !!!!
		_word = ch;
		ch = _file.peek();
		while (ch != EOF && !std::isspace(ch) && ch != '{' && ch != '}' && ch != ';') {
			_word += static_cast<char>(_file.get());
			ch = _file.peek();
		}
		return (setType(WORD));
	}

private:
	void skipWhiteSpaceAndComments(void) {
		char	ch;
		while ((ch = _file.peek()) != EOF) {
			if (std::isspace(ch)) {
				if (ch == '\n')
					++_line;
				_file.get();
				continue;
			}
			if (ch == '#') {
				while (ch != EOF && ch != '\n')
					ch = _file.get();
				++_line;
				continue;
			}
			break;
		}
	}
};

#endif
