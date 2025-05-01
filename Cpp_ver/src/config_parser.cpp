

#include <iostream>
#include <string>
#include <sstream>
#include "config_parser.hpp"

#include "module.hpp"

#include "config_directives.hpp"
#include "config_Token.hpp"

#include "Http.hpp"

void	parse(std::ifstream	&file) {
	Token	token(file);
	token.nextToken();

	if (token.getType() == Token::BEGIN_BLOCK || token.getWord() != Name::HTTP) {
		std::ostringstream	oss;
		oss << "NOT HTTP AND EMPTY DIRECTIVE!!!!!!!!!!!\n";
		throw (std::runtime_error(oss.str()));
	}
	// token.setBlock(Block::getType(token.getWord()));
	parseBlock(token);
}

void parseBlock(Token &token) {
	while (token.getType() != Token::END_BLOCK && token.getType() != Token::END_FILE) {
		if (token.getType() == Token::WORD) {
			parseDirective(token);
		} else if (token.getType() == Token::BEGIN_BLOCK) {
			std::ostringstream	oss;
			oss << H_BLU "THE VERY GRAND NEW EMPTY DIRECTIVE!!!!!!!!!!!\n" RST;
			throw (std::runtime_error(oss.str()));
		} else {
			std::ostringstream	oss;
			oss << "Unexpected token " << token.getType() << " in block: {"
				<< token.getWord() << "}\n";
			throw (std::runtime_error(oss.str()));
		}
	}

	// consume the closing '}'
	if (token.getType() == Token::END_BLOCK)
		token.nextToken();
}

void parseDirective(Token &token) {
	Token		contextToken(token);
	BlockType	previusBlock = contextToken.getBlock();
	std::string directive = contextToken.getWord();
	token.nextToken();

	// collect args until ';' or '{'
	std::vector<std::string> args;
	while (token.getType() == Token::WORD) {
		args.push_back(token.getWord());
		token.nextToken();
	}

	if (token.getType() == Token::END_STATEMENT) {
		// simple directive
		// REVIEW DISPATCH DIRECTIVE FUNC
		// handler_t	handle = Handle::dispatch(contextToken);
		// (void)handle;

		handleDirective(directive, args);
		token.nextToken();
	} else if (token.getType() == Token::BEGIN_BLOCK) {
		// directive with nested block
		token.setBlock(Block::getType(directive));
		BlockType atcualBlock = token.getBlock();

		// std::cout << TEAL "[" << directive << "] " << atcualBlock << " | " << previusBlock << RENDL;
		// std::cout << TEAL "[" << directive << "] " << atcualBlock.to_ulong() << " | " << previusBlock.to_ulong() << RENDL;

		if (atcualBlock.to_ulong() >= previusBlock.to_ulong()) {
			std::ostringstream	oss;
			oss << atcualBlock << " | " << previusBlock <<" SAME BLOCK CONTEXTBlock!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		} else if (atcualBlock.test(Module::LOCATION) && previusBlock.test(Module::HTTP)) {
			std::ostringstream	oss;
			oss << atcualBlock << " | " << previusBlock <<" OUT OF PALCE LOCATION CONTEXTBlock!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		}

		handleDirectiveStart(directive, args);
		token.nextToken();
		parseBlock(token);
		handleDirectiveEnd(directive, args);
		token.setBlock(previusBlock);

		if (contextToken.getWord() == "http") {
			if (token.getType() != Token::END_FILE) {
				std::ostringstream	oss;
				oss << "HTTP IS CLOSED/n" << token.getWord() << "\n";
				throw (std::runtime_error(oss.str()));
			}
		}
	} else {
		std::ostringstream	oss;
		oss << "Expected ';' or '{' after directive '"
				  << directive << "'\n";
		throw (std::runtime_error(oss.str()));
	}
}

void	handleDirective(const std::string &directive,
	const std::vector<std::string> &args) {
	(void)args;
	std::cout << "Directive: " << directive;
	for (size_t i = 0; i < args.size(); ++i) {
		std::cout << " [" << args[i] << "]";
	}
	std::cout << "\n";
}

void handleDirectiveStart(const std::string &directive,
	const std::vector<std::string> &args) {
		// DO SOMETHING??
		std::cout << BOLD BLU "BEGIN BLOCK: " GRN << directive << RENDL;
		(void)args;
}

void handleDirectiveEnd(const std::string &directive,
	const std::vector<std::string> &args) {
		(void)args;
		std::cout << RED "End Block: " << directive << RENDL;
}
