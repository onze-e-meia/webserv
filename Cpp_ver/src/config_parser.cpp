




#include <iostream>
#include <string>
#include <sstream>

#include "config_parser.hpp"
#include "module.hpp"
// #include "config_directives.hpp"
#include "Http.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */
void	Parser::parseBlock(void) {
	Token::tokenType_e	tokenType = _token.getType();
	// while (_token.getType() != Token::END_BLOCK && _token.getType() != Token::END_FILE) {
	while (tokenType != Token::END_BLOCK && tokenType != Token::END_FILE) {
		if (tokenType == Token::WORD) {
			parseDirective();
		} else if (tokenType == Token::BEGIN_BLOCK) {
			std::ostringstream	oss;
			oss << H_BLU "THE VERY GRAND NEW EMPTY DIRECTIVE!!!!!!!!!!!\n" RST;
			throw (std::runtime_error(oss.str()));
		} else if (tokenType == Token::END_STATEMENT) {
			_token.nextToken();
		} else {
			std::ostringstream	oss;
			oss << "Unexpected token " << tokenType << " in block: {"
				<< _token.getWord() << "}\n";
			throw (std::runtime_error(oss.str()));
		}
		tokenType = _token.getType();
	}
	// consume the closing '}'
	if (tokenType == Token::END_BLOCK)
		_token.nextToken();
}

void Parser::parseDirective(void) {
	BlockType	previusBlock = _token.getBlock();
	std::string	directiveName = _token.getWord();

	_wordStartPos = _token.getWordStartPos();
	_token.nextToken();

	// collect args until ';' or '{'
	// CAN BE A FUNCTION
	std::vector<std::string> args;
	while (_token.getType() == Token::WORD) {
		args.push_back(_token.getWord());
		_token.nextToken();
	}

	if (_token.getType() == Token::END_STATEMENT) {
		// simple directive
		// REVIEW DISPATCH DIRECTIVE FUNC
		// handler_t	handle = Handle::dispatch(contextToken);
		// (void)handle;

		handleDirective(directiveName, args);
		_token.nextToken();
	} else if (_token.getType() == Token::BEGIN_BLOCK) {
		// directive with nested block
		_token.setBlock(Block::getType(directiveName));
		BlockType atcualBlock = _token.getBlock();

		// std::cout << TEAL "[" << directive << "] " << atcualBlock << " | " << previusBlock << RENDL;
		// std::cout << TEAL "[" << directive << "] " << atcualBlock.to_ulong() << " | " << previusBlock.to_ulong() << RENDL;

		handleBlockStart(directiveName, args);
		if (atcualBlock <= previusBlock) {
			std::ostringstream	oss;
			oss << atcualBlock << " | " << previusBlock <<" SAME BLOCK CONTEXTBlock!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		} else if (atcualBlock == Block::LOCATION && previusBlock == Block::HTTP) {
			std::ostringstream	oss;
			oss << atcualBlock << " | " << previusBlock <<" OUT OF PALCE LOCATION CONTEXTBlock!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		}
		Http::addBlock(atcualBlock);

		_token.nextToken();
		parseBlock();
		handleBlockEnd(directiveName, args);

		_token.setBlock(previusBlock);

		if (previusBlock == Block::EMPTY) {
			if (_token.getType() != Token::END_FILE) {
				std::ostringstream	oss;
				oss << "HTTP IS CLOSED/n" << _token.getWord() << "\n";
				throw (std::runtime_error(oss.str()));
			}
		}
	} else {
		std::ostringstream	oss;
		oss << "Expected ';' or '{' after directive '"
				  << directiveName << "'\n";
		throw (std::runtime_error(oss.str()));
	}
}

void	Parser::handleDirective(std::string name,const std::vector<std::string> &args) {
	(void)args;
	std::cout << "Directive: " << name;
	for (size_t i = 0; i < args.size(); ++i) {
		std::cout << " [" << args[i] << "]";
	}
	std::cout << YLW " { on line: " << _token.getLine() << " : " << _wordStartPos << " }" RENDL;
}

void Parser::handleBlockStart(std::string name,const std::vector<std::string> &args) {
		// DO SOMETHING??
		std::cout << BOLD BLU "BEGIN BLOCK: " GRN << name << RENDL;
		(void)args;
}

void Parser::handleBlockEnd(std::string name, const std::vector<std::string> &args) {
		// DO SOMETHING??
		(void)args;
		std::cout << RED "End Block: " << name << RENDL;
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Parser::Parser(std::ifstream &file): _token(file), _wordStartPos(0) {}

/* Member Functions */
void	Parser::parseConfigFile(void) {
	_token.nextToken();
	if (_token.getWord() != Name::HTTP) {
		if (_token.getType() == Token::BEGIN_BLOCK)
			throw (Http::EmptyBlock(_token.getLine(), _token.getWordStartPos()));
		throw (Http::WrongBlock(_token.getWord(), _token.getLine(), _token.getWordStartPos()));
	}
	parseBlock();
}
