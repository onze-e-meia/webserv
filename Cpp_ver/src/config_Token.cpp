

#include "config_Token.hpp"
#include "module.hpp"

Token::Token(std::ifstream	&file):
	_blockType(Block::EMPTY), _tokenType(EMPTY), _file(file),
	_pos(0), _line(1) { _word.reserve(64); }

Token::Token(const Token &other):
	_blockType(other._blockType), _tokenType(other._tokenType), _word(other._word),
	_file(other._file), _pos(other._pos), _line(other._line) {}

void	Token::setType(tokenType_e tokenType) {
	_tokenType = tokenType;
}

void	Token::setBlock(BlockType blockType) {
	_blockType = blockType;
}

Token::tokenType_e	Token::getType() const {
	return (_tokenType);
}

BlockType	Token::getBlock() const {
	return (_blockType);
}

const	std::string &Token::getWord() const {
	return (_word);
}
