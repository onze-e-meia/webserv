




#include <cstdio>
#include "Token.hpp"
#include "Parser.hpp"

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

/* Contsructor & Destructor */
Token::Token(char *const path, std::istream &file):
_type(EMPTY), _wordStartPos(0),_csFile(path, file) {
	_word.reserve(MAX_DIRECTIVE_LEN);
}

Token::~Token(void) {}

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
		ch = static_cast<char>(_csFile.get());
		if (_word.length() + 1 > MAX_DIRECTIVE_LEN)
			throw (Parser::DirectiveLength(_csFile.getPath(), _csFile.cursorLine(), _wordStartPos, _word));
		_word += ch;
		ch = _csFile.peek();
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

std::string Token::getWord() const {
	return (_word);
}

std::string	Token::getPath(void) const {
	return (_csFile.getPath());
}

size_t	Token::cursorLine(void) const {
	return (_csFile.cursorLine());
}

std::size_t	Token::cursorPos(void) const {
	return(_csFile.cursorPos());
}

size_t	Token::getWordStartPos(void) const {
	 return (_wordStartPos);
}
