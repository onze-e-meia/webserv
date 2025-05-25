




#include <iostream>
#include <string>

#include "Parser.hpp"
#include "Webserv.hpp"

#include "color.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */
void	Parser::parseBlock(void) {
	Token::type_e	tokenType = _token.getType();

	while (tokenType != Token::END_BLOCK && tokenType != Token::END_FILE) {
		if (tokenType == Token::WORD) {
			parseDirective();
		} else if (tokenType == Token::BEGIN_BLOCK) {
			throw (Parser::WrongBlock(*this, _token.getWord(), this->_innerBlock));
		} else if (tokenType == Token::END_STATEMENT) {
			_token.nextToken();
		} else
			throw (Parser::Exception(*this, "Unexpected Token Error."));
		tokenType = _token.getType();
	}

	if (_token.getType() == Token::END_FILE && (_innerBlock != Block::WEBSERV))
		throw (Parser::Exception(*this, _innerBlock._name + " block is not clossed, missig '}'."));
	if (tokenType == Token::END_BLOCK) // consume the closing '}'
		_token.nextToken();
}

void Parser::parseDirective(void) {
	Block::Module				outerBlock = _innerBlock;
	C_Str						directive = _token.getWord();
	std::vector<std::string>	args;

	_wordStartPos = _token.getWordStartPos();
	_token.nextToken();
	collectArgs(args);
	if (_token.getType() == Token::END_STATEMENT) { // simple directive
		handleDirective(outerBlock, directive, args);
	} else if (_token.getType() == Token::BEGIN_BLOCK) { // directive with nested block
		handleBlockStart(outerBlock, directive, args);
		parseBlock();
		handleBlockEnd(outerBlock, directive, args); // TODO: Check if all needed directives are set.
	} else
		throw (Parser::ExpectedToken(*this, directive));
}

void	Parser::collectArgs(std::vector<std::string> &args) {
	while (_token.getType() == Token::WORD) { // collect args until ';' or '{'
		args.push_back(_token.getWord());
		_token.nextToken();
	}
}

void	Parser::handleDirective(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args) {
	Webserv::dispatchHandler(*this, directive, outerBlock, args); // TODO: Check for nb of args.
	_token.nextToken();
}

void Parser::handleBlockStart(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args) {
	std::cout << BOLD BLU "BEGIN BLOCK: " GRN << directive << RST;
	std::cout << YLW " { on line: " << _token.cursorLine() << " : " << _wordStartPos << " }" RENDL;

	_innerBlock = Block::dispatchType(directive);
	if (!Block::validOrder(outerBlock, _innerBlock)) {
		throw (Parser::WrongBlock(*this, directive, outerBlock));
	} else if (!Block::validNbArgs(_innerBlock, args))
		throw (Parser::WrongArgs(*this, directive, outerBlock, args));
	Webserv::addBlock(_innerBlock, args);
	_token.nextToken();
}

void Parser::handleBlockEnd(const Block::Module &outerBlock, C_Str &directive, C_VecStr &args) {
	(void)args; // TODO: FIX this, need it here??
	std::cout << RED ">> End Block: " << directive << RENDL;

	_innerBlock = outerBlock;
	if (outerBlock == Block::WEBSERV && _token.getType() != Token::END_FILE)
		throw (Parser::Exception(*this, "Closing curly brackets '}' has been set. Any further text is out of the 'http' Block"));
}


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor & Destructor */
Parser::Parser(void):
_token(Webserv::getPath(), Webserv::getFile()), _innerBlock(Block::WEBSERV), _wordStartPos(0) {}

Parser::~Parser(void) {}

/* Getters */
Token	Parser::getToken(void) const {
	return (_token);
}

Block::Module	Parser::getInnerBlock(void) const {
	return (_innerBlock);
}

std::size_t	Parser::getWordStartPos(void) const {
	return (_wordStartPos);
}

/* Member Functions */
void	Parser::parseConfigFile(void) {
	_token.nextToken();
	parseBlock();
	if (!Webserv::checkInstance())
		throw (Parser::Exception(*this, "The configuratio file is empty."));
}
