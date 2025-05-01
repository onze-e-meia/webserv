

#include <iostream>
#include <string>
#include <sstream>
#include "config_parser.hpp"

#include "module.hpp"

#include "config_directives.hpp"
#include "config_Token.hpp"

#include "Http.hpp"
// class Http;

struct ConfigParser {
	bool		http;
	blockType_e	context;
	blockType_e	previus;

	//NEW
	BlockType 	cont;
	BlockType 	prev;
}; // ConfigParser

void	parse(std::ifstream	&file) {
	Token			token(file);
	ConfigParser	conf = {
		false, BLOCK_INIT, BLOCK_INIT
		// BlockN::MAP.find(Name::EMPTY)->second, BlockN::MAP.find(Name::EMPTY)->second
	};

	// conf.cont.reset();
	// conf.prev.reset();
	conf.cont.set(Module::EMPTY);
	conf.prev.set(Module::EMPTY);
	token.nextToken();
	if (token.getType() == TOKEN_BEGIN_BLOCK) {
		std::ostringstream	oss;
		oss << "NOT HTTP AND EMPTY DIRECTIVE!!!!!!!!!!!\n";
		throw (std::runtime_error(oss.str()));
	}

	std::cout << conf.cont << conf.prev << ENDL;

	const Block	block;
	Http		http;

	parseBlock(token, conf, block);

}

void parseBlock(Token &token, ConfigParser conf, Block block) {

	// We're either at start-of-file (no '{') or right after a '{'
	// token.nextToken();
	if (token.getType() == TOKEN_BEGIN_BLOCK)
		token.nextToken();

	while (token.getType() != TOKEN_END_BLOCK && token.getType() != TOKEN_EOF) {

		if (token._closed) {
			std::ostringstream	oss;
			oss << "01 HTTP IS CLOSED/n" << token.getWord() << "\n";
			throw (std::runtime_error(oss.str()));
		}

		if (token.getType() == TOKEN_WORD) {
			parseDirective(token, conf, block);
		} else{
			std::ostringstream	oss;
			oss << "Unexpected token in block: "
				<< token.getWord() << "\n";
			throw (std::runtime_error(oss.str()));
		}
	}

	// consume the closing '}'
	if (token.getType() == TOKEN_END_BLOCK)
		token.nextToken();
}

void parseDirective(Token &token, ConfigParser conf, Block blocckk) {

	Token	start(token);
	std::string directive = token.getWord();
	token.nextToken();

	// collect args until ';' or '{'
	std::vector<std::string> args;
	while (token.getType() == TOKEN_WORD) {
		args.push_back(token.getWord());
		token.nextToken();
	}

	if (token.getType() == TOKEN_END_STATEMENT) {
		// simple directive

		// REVIEW DISPATCH DIRECTIVE FUNC
		// handler_t	handle = Handle::dispatch(start);
		// (void)handle;

		handleDirective(directive, args);
		token.nextToken();
	} else if (token.getType() == TOKEN_BEGIN_BLOCK) {
		// directive with nested block
		// token.setBlock(blocckk.dispatch(start));
		blockType_e	block = token.getBlock();

		// NEW
		token.setFlags(BlockN::dispatch(directive));
		// NEW
		BlockType flags = token.getFlgas();


		// WHAT THIS CONTROL?? Look block constructor!!
		// if (block == BLOCK_INIT) {
		if (flags == conf.context) {
			std::ostringstream	oss;
			oss << block << " Unknown WHAT IS THIS DIRECTIVE!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		}

		conf.previus = conf.context;
		conf.prev = conf.cont;
		std::cout << TEAL "[" << directive << "] " << block << " | " << conf.context << RENDL;
		std::cout << TEAL "[" << directive << "] " << flags << " | " << conf.cont << RENDL;
		std::cout << TEAL "[" << directive << "] " << flags.to_ulong() << " | " << conf.cont.to_ulong() << RENDL;

		// if (!conf.http && token.getBlock() != BLOCK_HTTP) {
		// if (!conf.http && token.getFlgas() != BlockN::SPECS[1].flags) {
		// DONT NEED THIS
		if (!conf.http && token.getFlgas() != BlockN::MAP.find(Name::HTTP)->second) {
			std::ostringstream	oss;
			oss << "NOT HTTP!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str())); // TIL THIS
		// } else if (block <= conf.context) {
		} else if (flags.to_ulong() >= conf.cont.to_ulong()) {
			std::ostringstream	oss;
			oss << block << conf.context <<"SAME BLOCK CONTEXT!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		// } else if (block == BLOCK_LOCATION && conf.context == BLOCK_HTTP) {
		// } else if (flags.test(Module::LOCATION) && conf.cont.test(Module::HTTP)) {
		} else if (conf.cont.test(Module::HTTP) && directive == Name::LOCATION) {
			std::ostringstream	oss;
			oss << block << conf.context <<"OUT OF PALCE LOCATION CONTEXT!!!!!!!!!!!\n";
			throw (std::runtime_error(oss.str()));
		} else {
			conf.http = true;
		}
		conf.context = block;
		conf.cont = flags;

		handleDirectiveStart(directive, args);
		token.nextToken();
		if (token.getType() == TOKEN_BEGIN_BLOCK) {
				std::ostringstream	oss;
				oss << "EMPTY DIRECTIVE!!!!!!!!!!!\n";
				throw (std::runtime_error(oss.str()));
		}

		parseBlock(token, conf, blocckk);
		handleDirectiveEnd(directive, args);

		if (start.getWord() == "http") {
			std::cout << "HTTP IS NOW FALSE!!\n";
			token._closed = true;
			token.setBlock(BLOCK_INIT);
		}
		token.setBlock(conf.previus);
		// token.setBlock(token.getPrevius());
		// token.setContext(token.getPrevius());

		// conf.context = conf.previus;
	} else{
		std::cerr << "Expected ';' or '{' after directive '"
				  << directive << "'\n";
		// std::exit(1);
		return ;
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
		(void)args;
		std::cout << "Begin Block: " << directive << "\n";
}

void handleDirectiveEnd(const std::string &directive,
	const std::vector<std::string> &args) {
		(void)args;
		std::cout << RED "End Block: " << directive << RENDL;
}
