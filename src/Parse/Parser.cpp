




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
	Token::tokenType_e	tokenType = _token.getType();

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
	Block::type_e		previusBlock = _token.getBlock();
	const std::string	previusName = Block::getName(previusBlock);
	const std::string	directiveName = _token.getWord();

	_wordStartPos = _token.getWordStartPos(); // _wordStartPos don't need to be a member
	// should get lineStartPos to
	_token.nextToken();
	std::vector<std::string> args;
	while (_token.getType() == Token::WORD) { // collect args until ';' or '{' // CAN BE A FUNCTION ?
		args.push_back(_token.getWord());
		_token.nextToken();
	}

	if (_token.getType() == Token::END_STATEMENT) { // simple directive // CAN BE A FUNCTION ?
		if (directiveName == Name::HTTP) // This will be solved with directives handler, ther will be no http plain directive
			throw (std::runtime_error(" 'http' is a Block, not plain directive!/n'"));
		// REVIEW DISPATCH DIRECTIVE FUNC // Check for args for eache individual directive

		// Http::dispatchHandler(previusBlock, directiveName, args);
		Webserv::dispatchHandler(previusBlock, directiveName, args);

		// handler_t	handle = Handle::dispatch(contextToken);
		// (void)handle;
		handleDirective(directiveName, args);
		_token.nextToken();
	} else if (_token.getType() == Token::BEGIN_BLOCK) { // directive with nested block
		_token.setBlock(Block::dispatchType(directiveName));
		Block::type_e	actualBlock = _token.getBlock();

		handleBlockStart(directiveName, args); // All below can be handle block function
		if (actualBlock == Block::EMPTY) {
			throw (Parser::UnknownDirective(directiveName, _token.getLine(), _wordStartPos));
		} else if (!args.empty() && (actualBlock == Block::HTTP || actualBlock == Block::SERVER)) {
			throw (std::runtime_error(" 'http' is a Block, it dont have args!/n'")); // still need to check args for http
		} else if (actualBlock <= previusBlock) {
			if (actualBlock == previusBlock)
				throw (Parser::SameBlock(directiveName, previusName, _token.getLine(), _wordStartPos));
			throw (Parser::WrongBlock(directiveName, previusName, _token.getLine(), _wordStartPos));
		} else if (actualBlock == Block::LOCATION && previusBlock == Block::HTTP)
			throw (Parser::WrongBlock(directiveName, previusName, _token.getLine(), _wordStartPos));

		Webserv::addBlock(actualBlock);

		_token.nextToken();
		parseBlock();
		handleBlockEnd(directiveName, args); // What in here???

		_token.setBlock(previusBlock);

		if (previusBlock == Block::EMPTY && _token.getType() != Token::END_FILE)
			throw (Parser::HttpClosed(_token.getLine(), _wordStartPos));
	} else
		throw (Parser::ExpectedToken(directiveName, _token.getLine(), _token.getWordStartPos()));
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
// Parser::Parser(void) {}
Parser::Parser(std::ifstream &file): _token(file), _wordStartPos(0) {}

/* Member Functions */
void	Parser::parseConfigFile(void) {
	_token.nextToken();
	if (_token.getWord() != Name::HTTP) {
		throw (Parser::FirstBlock(_token.getWord(), _token.getLine(), _token.getWordStartPos()));
	}
	parseBlock();
}
