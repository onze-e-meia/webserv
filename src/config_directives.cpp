

#include <iostream>
// #include "config_Token.hpp"
#include "config_directives.hpp"
#include "color.hpp"

class Token;
// const directives_map NULL_DIRECTIVES = {
// 	{ "http", Handle::http },
// };

// const directives_map HTTP_DIRECTIVES = {
// 	{ "include", Handle::include },
// 	{ "server", Handle::server },
// };

// const directives_map SERVER_DIRECTIVES = {
// 	{ "host", Handle::host },
// 	{ "port", Handle::port },
// 	{ "listen", Handle::listen },
// 	{ "server_name", Handle::server_name },


// static const directives_map CORE_DIRECTIVES = {
// 	{ "root", Handle::root },
// 	{ "index", Handle::index },
// 	{ "autoindex", Handle::autoindex },
// 	{ "error_page", Handle::error_page },
// 	{ "client_max_body_size", Handle::client_max_body_size },
// 	{ "methods", Handle::allow_methods },
// 	{ "sendfile", Handle::sendfile },
// 	{ "keepalive_timeout", Handle::keepalive_timeout } ,
// };

Directive::Directive(Token &token) {
	const directiveSet_e	blocks[] = {INIT_D, HTTP_D, SERVER_D, CORE_D};
	const DirectivePair		*directiveSet[] = {
		DirectiveSet::INIT_S,
		DirectiveSet::HTTP_S,
		DirectiveSet::SERVER_S,
		DirectiveSet::CORE_S
	};

	// for (size_t j = 0; j < 4; ++j) {
	// 	for (size_t i = 0; directiveSet[j] != NULL; ++i) {
	// 		if (token.getBlock() & blocks[i])
	// 			_map[directiveSet[j][i].directiveName] = directiveSet[j][i].directiveHandler;
	// 	}
	// }
}

// directives_map	buidlDirectivedMap(blockType_e block) {
// 	directives_map	map;
// 	if (block == BLOCK_HTTP) {
// 		for (u_short i = 0; i < 3; ++i)
// 			map[Directive::HTTP[i].directiveName] = Directive::HTTP[i].directiveHandler;
// 	}
// 	if (block == BLOCK_SERVER) {
// 		for (u_short i = 0; i < 5; ++i)
// 			map[Directive::HTTP[i].directiveName] = Directive::HTTP[i].directiveHandler;
// 	}
// 	if (block == BLOCK_LOCATION) {
// 		for (u_short i = 0; i < 8; ++i)
// 			map[Directive::HTTP[i].directiveName] = Directive::HTTP[i].directiveHandler;
// 	}
// 	return (map);
// }

// static const directives_map &directiveMatch(int	block) {
// 	if (block == BLOCK_HTTP)
// 		return HTTP_DIRECTIVES;
// 	if (block == BLOCK_SERVER)
// 		return SERVER_DIRECTIVES;
// 	if (block == BLOCK_HTTP | BLOCK_SERVER | BLOCK_LOCATION)
// 		return CORE_DIRECTIVES;
// 	return NULL_DIRECTIVES;
// }

// static const handler_t	blockDirectives(Token &token, int block) {
// 	const directives_map	&map = directiveMatch(block);
// 	directives_it	it = map.find(token.getWord());
// 	directives_it	end = map.end();
// 	if (it == end)
// 		return NULL;
// 	std::cout << BLU "DIRECTIVE: " GRN << token.getWord() << "{{" << map.begin()->first << "}}" RENDL;
// 	return (*it->second);
// }

// handler_t	Block::http(Token &token) {
// 	directives_it	it = HTTP_DIRECTIVES.find(token.getWord());
// 	directives_it	end = HTTP_DIRECTIVES.end();
// 	if (it == end)
// 		return NULL;
// 	std::cout << BLU "DIRECTIVE: " GRN << token.getWord() << RENDL;
// 	return (*it->second);
// }

// handler_t	Block::server(Token &token) {
// 	directives_it	it = SERVER_DIRECTIVES.find(token.getWord());
// 	directives_it	end = SERVER_DIRECTIVES.end();
// 	if (it == end)
// 		return NULL;
// 	std::cout << BLU "DIRECTIVE: " GRN << token.getWord() << RENDL;
// 	return (*it->second);
// }

// handler_t	Block::location(Token &token) {
// 	directives_it	it = CORE_DIRECTIVES.find(token.getWord());
// 	directives_it	end = CORE_DIRECTIVES.end();
// 	if (it == end)
// 		return NULL;
// 	std::cout << BLU "DIRECTIVE: " GRN << token.getWord() << RENDL;
// 	return (*it->second);
// }

// handler_t	Handle::dispatch(Token &token) {
// 	// directive_it	it = CORE_DIRECTIVES.find(token.getWord());
// 	// directive_it	end = CORE_DIRECTIVES.end();
// 	// if (it == end) {
// 	// 	std::cerr << RED " >>>>>>>>>> Unknown directive: " << token.getWord() << RENDL;
// 	// 	return NULL;
// 	// }
// 	// std::cout << BLU "DIRECTIVE: " GRN << token.getWord() << RENDL;
// 	// return (*it->second);

// 	int	blocks[] = {BLOCK_HTTP, BLOCK_SERVER, BLOCK_HTTP | BLOCK_SERVER | BLOCK_LOCATION};
// 	for (short i = 0; i < 3; ++i) {
// 		if (token.getBlock() & blocks[i]) {
// 			Handler handle = blockDirectives(token, blocks[i]);
// 			if (handle) {
// 				return (handle);
// 			}
// 		}
// 	}
// 	std::cerr << RED " >>>>>>>>>> Unknown directive: " << token.getWord() << RENDL;
// 	return NULL;

// 	// if (token.getBlock() == BLOCK_HTTP) {
// 	// 	Handler	handle = Block::http(token);
// 	// 	if (handle)
// 	// 		return (handle);
// 	// }
// 	// if (token.getBlock() == BLOCK_SERVER) {
// 	// 	Handler	handle = Block::server(token);
// 	// 	if (handle)
// 	// 		return (handle);
// 	// }
// 	// if (token.getBlock() == BLOCK_HTTP | BLOCK_SERVER | BLOCK_LOCATION) {
// 	// 	Handler	handle = Block::location(token);
// 	// 	if (handle)
// 	// 		return (handle);
// 	// }
// 	// std::cerr << RED " >>>>>>>>>> Unknown directive: " << token.getWord() << RENDL;
// 	// return NULL;

// 	// for (int i = 0; directives[i].name != nullptr; ++i) {
// 	// 	// Compare token word with directive name
// 	// 	if (token.getWord() == directives[i].name) {
// 	// 		directives[i].handler(token);  // Call the handler for this directive
// 	// 		return;
// 	// 	}
// 	// }
// 	// std::cout << "Unknown directive: " << token.getWord() << "\n";
// }

void	Directive::http(Token &token) {

}

/* HTTP */
void	Directive::include(Token &token) {

}

void	Directive::server(Token &token) {

}

/* SERVER */
void	Directive::port(Token &token) {

}

void	Directive::host(Token &token) {

}

void	Directive::listen(Token &token) {

}

void	Directive::server_name(Token &token) {

}

void	Directive::location(Token &token) {

}

/* LOCATION */
void	Directive::root(Token &token) {

}

void	Directive::index(Token &token) {

}

void	Directive::autoindex (Token &toke) {

}

void	Directive::error_page(Token &token) {

}

void	Directive::client_max_body_size(Token &token) {

}

void	Directive::allow_methods(Token &token) {

}

void	Directive::sendfile(Token &token) {

}

void	Directive::keepalive_timeout(Token &token) {

}
