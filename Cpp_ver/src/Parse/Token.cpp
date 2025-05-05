




#include <cstdio>
#include "Token.hpp"
#include "Parser.hpp"
#include "ParseLimits.hpp"
#include "module.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */
void Token::skipWhiteSpaceAndComments(void) {
	char	ch;
	while ((ch = _file.peek()) != EOF) {
		if (std::isspace(ch)) {
			_file.get();
			continue;
		}
		if (ch == '#') {
			while (ch != EOF && ch != '\n')
				ch = _file.get();
			continue;
		}
		// Check for line size.
		// Check for file size.
		break;
	}
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Token::Token(std::istream &file):
	_tokenType(EMPTY), _blockType(Block::EMPTY), _wordStartPos(0),
	_file(file) { _word.reserve(64); }

/* Setters */
void	Token::setType(tokenType_e tokenType) {
	_tokenType = tokenType;
}

void	Token::setBlock(BlockType blockType) {
	_blockType = blockType;
}

/* Getters */
Token::tokenType_e	Token::getType() const {
	return (_tokenType);
}

BlockType	Token::getBlock() const {
	return (_blockType);
}

const	std::string &Token::getWord() const {
	return (_word);
}

size_t	Token::getWordStartPos(void) const {
	 return (_wordStartPos);
}

size_t	Token::getLine(void) const {
	return (_file.cursorLine());
}

/* Member Functions */
void	Token::nextToken(void) {
	skipWhiteSpaceAndComments();
	_word.clear();
	char	ch = _file.get();
	_wordStartPos = _file.cursorPos();
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
		if (_word.length() > MAX_DIRECTIVE_LEN)
			throw (Parser::DirectiveLength(_word, _file.cursorLine(), _wordStartPos));
	}
	return (setType(WORD));
}
