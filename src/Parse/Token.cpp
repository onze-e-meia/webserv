




#include <cstdio>
#include "Token.hpp"
#include "Parser.hpp"
#include "ParseLimits.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */
void Token::skipWhiteSpaceAndComments(void) {
	char	ch;
	while ((ch = _csFile.peek()) != EOF) {
		if (std::isspace(ch)) {
			_csFile.get();
			continue;
		}
		if (ch == '#') {
			while (ch != EOF && ch != '\n')
				ch = _csFile.get();
			continue;
		}
		break;
	}
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Token::Token(char *const path, std::istream &file):
_type(EMPTY), _wordStartPos(0),_csFile(path, file) {
	_word.reserve(MAX_DIRECTIVE_LEN);
}

/* Member Functions */
void	Token::nextToken(void) {
	skipWhiteSpaceAndComments();
	_word.clear();
	char	ch = _csFile.get();
	_wordStartPos = _csFile.cursorPos();
	if (ch == EOF)
		return (setType(END_FILE));
	else if (ch == '{')
		return (setType(BEGIN_BLOCK));
	else if (ch == '}')
		return (setType(END_BLOCK));
	else if (ch == ';')
		return (setType(END_STATEMENT));

	_word = static_cast<char>(ch);
	ch = _csFile.peek();
	while (ch != EOF && !std::isspace(ch) && ch != '{' && ch != '}' && ch != ';' && ch != '#') {
		_word += static_cast<char>(_csFile.get());
		ch = _csFile.peek();
		if (_word.length() > MAX_DIRECTIVE_LEN)
			throw (Parser::DirectiveLength(_word, _csFile.cursorLine(), _wordStartPos));
	}

	return (setType(WORD));
}

/* Setters */
void	Token::setType(type_e type) {
	_type = type;
}

/* Getters */
Token::type_e	Token::getType() const {
	return (_type);
}

const	std::string &Token::getWord() const {
	return (_word);
}

size_t	Token::getWordStartPos(void) const {
	 return (_wordStartPos);
}

size_t	Token::getLine(void) const {
	return (_csFile.cursorLine());
}
