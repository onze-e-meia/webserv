




#include <iostream>
#include <string>
// #include <sstream>

#include "Parser.hpp"
#include "Module.hpp"
#include "Http.hpp"
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
			throw (Parser::EmptyBlock(_token.getLine(), _token.getWordStartPos()));
		} else if (tokenType == Token::END_STATEMENT) {
			_token.nextToken();
		} else // Does any error get in here ?
			throw (Parser::UnexpectedToken(_token.getWord(), _token.getLine(), _token.getWordStartPos()));
		tokenType = _token.getType();
	}
	if (tokenType == Token::END_BLOCK) // consume the closing '}'
		_token.nextToken();
}

void Parser::parseDirective(void) {
	Block::Module		outerBlock = _innerBlock;
	const std::string	directive = _token.getWord();

	_wordStartPos = _token.getWordStartPos(); // _wordStartPos don't need to be a member
	// should get lineStartPos to??
	_token.nextToken();
	std::vector<std::string> args;
	while (_token.getType() == Token::WORD) { // collect args until ';' or '{' // CAN BE A FUNCTION ?
		args.push_back(_token.getWord());
		_token.nextToken();
	}

	if (_token.getType() == Token::END_STATEMENT) { // simple directive // CAN BE A FUNCTION ?
		Webserv::dispatchHandler(outerBlock, directive, args); // TODO: Check for nb of args.
		handleDirective(directive, args);
		_token.nextToken();
	} else if (_token.getType() == Token::BEGIN_BLOCK) { // directive with nested block
		_innerBlock = Block::dispatchType(directive);

		handleBlockStart(directive, args); // All bellow can be handle block function
		if (!Block::validOrder(outerBlock, _innerBlock)) { // TODO: in error msg also show the args followed by '{'
			throw (Parser::WrongBlock(directive, outerBlock._name, _token.getLine(), _wordStartPos));
		} else if (!Block::validNbArgs(_innerBlock, args)) {
			throw (std::runtime_error(" 'http' is a Block, it dont have args!/n'")); // TODO: error msg.
		}
		Webserv::addBlock(_innerBlock, args);

		_token.nextToken();
		parseBlock();

		handleBlockEnd(directive, args); // TODO: Check if all needed directives are set.
		_innerBlock = outerBlock;
		if (outerBlock == Block::EMPTY && _token.getType() != Token::END_FILE)
			throw (Parser::HttpClosed(_token.getLine(), _wordStartPos));

	} else
		throw (Parser::ExpectedToken(directive, _token.getLine(), _token.getWordStartPos()));
}

void	Parser::handleDirective(const std::string &name, const std::vector<std::string> &args) {
	(void)args;
	// std::cout << "Directive: " << name;
	// for (size_t i = 0; i < args.size(); ++i) {
	// 	std::cout << " [" << args[i] << "]";
	// }
	// std::cout << YLW " { on line: " << _token.getLine() << " : " << _wordStartPos << " }" RENDL;
}

void Parser::handleBlockStart(const std::string &name, const std::vector<std::string> &args) {
		// DO SOMETHING??
		std::cout << BOLD BLU "BEGIN BLOCK: " GRN << name << RST;
		std::cout << YLW " { on line: " << _token.getLine() << " : " << _wordStartPos << " }" RENDL;
		(void)args;
}

void Parser::handleBlockEnd(const std::string &name, const std::vector<std::string> &args) {
		// DO SOMETHING??
		(void)args;
		std::cout << RED "End Block: " << name << RENDL;
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Parser::Parser(void):
_token(Webserv::getPath(), Webserv::getFile()), _innerBlock(Block::EMPTY), _wordStartPos(0) {}

/* Member Functions */
void	Parser::parseConfigFile(void) {
	_token.nextToken();
	if (_token.getWord() != Name::HTTP) {
		throw (Parser::FirstBlock(_token.getWord(), _token.getLine(), _token.getWordStartPos()));
	}
	parseBlock();
}
