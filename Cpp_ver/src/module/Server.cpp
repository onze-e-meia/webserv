




#include "Server.hpp"

#define SEVER_NAME_HANDLER(name) { #name, static_cast<handler_t>(&Server::name##_Handler) }

static const NameHandler	SERVER_HANDLER[] = {
	SEVER_NAME_HANDLER(server_name),
	SEVER_NAME_HANDLER(host),
	SEVER_NAME_HANDLER(port),
	SEVER_NAME_HANDLER(listen),
	{ "", NULL },
};

static const DirectiveMap	SEVER_MAP = Server::buildMap();

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Server::Server(void): Core(Block::SERVER) {
	// std::cout << YLW "SERVER ADDED TO HTTP " << _blockType  << RENDL;
}

/* Member Functions */
const DirectiveMap	Server::buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; SERVER_HANDLER[i]._handler != NULL; ++i)
		map[SERVER_HANDLER[i]._name] = SERVER_HANDLER[i]._handler;
	return (map);
}

const handler_t	Server::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = SEVER_MAP.find(name);
	DirectiveConst_it	end = SEVER_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

Block::type_e	Server::getBlockType(void) { return _blockType; }

void		Server::setName(const std::string &name) {_server_name = name; }

std::string	Server::getName(void) { return (_server_name); }

/* Handlers */
void	Server::server_name_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Server::host_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Server::port_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Server::listen_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}
