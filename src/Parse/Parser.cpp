




#include <iostream>
#include <string>
// #include <sstream>

#include "Parser.hpp"
#include "Webserv.hpp"

#include "color.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */
void	Parser::parseBlock(void) {
	Token::type_e	tokenType = _token.getType();
	// std::cerr << TEAL "PARSE BLOCK!!!!! toke: " << _token.getType() << RENDL;

	while (tokenType != Token::END_BLOCK && tokenType != Token::END_FILE) {
		if (tokenType == Token::WORD) {
			parseDirective();
			// std::cerr << TEAL "parseDirective() toke: " << _token.getType() << RENDL;
		} else if (tokenType == Token::BEGIN_BLOCK) {
			throw (Parser::WrongBlock(*this, _token.getWord(), this->_innerBlock));
		} else if (tokenType == Token::END_STATEMENT) {
			_token.nextToken();
			if (_token.getType() == Token::END_FILE)
				throw (Parser::Exception(*this, BLU "THE GRAND NEW Http block is not clossed, missig '}'." RST));
		} else if (tokenType == Token::EMPTY)
			throw (Parser::Exception(*this, "Unexpected Token Error."));
		tokenType = _token.getType();
	}
	// std::cerr << TEAL "PARSE BLOCK BEFFORE END BLOCK!!!!! " << _token.getType() << RENDL;
	if (tokenType == Token::END_BLOCK) {
		_token.nextToken();
	} // consume the closing '}'
}

void Parser::parseDirective(void) {
	Block::Module				outerBlock = _innerBlock;
	const std::string			directive = _token.getWord();
	std::vector<std::string>	args;

	_wordStartPos = _token.getWordStartPos();
	_token.nextToken();
	collectArgs(args);
	if (_token.getType() == Token::END_STATEMENT) { // simple directive

		handleDirective(outerBlock, directive, args);
	} else if (_token.getType() == Token::BEGIN_BLOCK) { // directive with nested block
		handleBlockStart(outerBlock, directive, args);
		// std::cerr << TEAL "HERE AFTER THE LAST TOKEN TYPE ???" RENDL;
		// std::cerr << BLU "0 TOKEM TYPE: " << _token.getType() << RENDL;
		// _token.nextToken();
		// std::cerr << BLU "1 TOKEM TYPE: " << _token.getType() << RENDL;

		parseBlock();
		// std::cerr << BLU "2 TOKEM TYPE: " << _token.getType() << RENDL;


		handleBlockEnd(outerBlock, directive, args); // TODO: Check if all needed directives are set.
	} else
		throw (Parser::ExpectedToken(*this, directive));

	// std::cerr << TEAL "0 FINAL TOKEM TYPE: " << _token.getType() << RENDL;
	if (outerBlock == Block::HTTP && _token.getType() == Token::END_FILE)
		throw (Parser::Exception(*this, "Http block is not clossed, missig '}'."));
	// std::cerr << TEAL "1 FINAL TOKEM TYPE: " << _token.getType() << RENDL;

}

void	Parser::collectArgs(std::vector<std::string> &args) {
	while (_token.getType() == Token::WORD) { // collect args until ';' or '{'
		args.push_back(_token.getWord());
		_token.nextToken();
	}
}

void	Parser::handleDirective(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args) {
	Webserv::dispatchHandler(outerBlock, directive, args); // TODO: Check for nb of args.
	_token.nextToken();
}

void Parser::handleBlockStart(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args) {
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

void Parser::handleBlockEnd(const Block::Module &outerBlock, const std::string &directive, const std::vector<std::string> &args) {
	std::cout << RED ">> End Block: " << directive << RENDL;

	_innerBlock = outerBlock;
	if (outerBlock == Block::WEBSERV && _token.getType() != Token::END_FILE)
		throw (Parser::Exception(*this, "Closing curly brackets '}' has been set. Any further text is out of the 'http' Block"));
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Parser::Parser(void):
_token(Webserv::getPath(), Webserv::getFile()), _innerBlock(Block::WEBSERV), _wordStartPos(0) {}

/* Member Functions */
void	Parser::parseConfigFile(void) {
	_token.nextToken();
	parseBlock();
	if (!Webserv::checkInstance())
		throw (Parser::Exception(*this, "The configuratio file is empty."));

}
