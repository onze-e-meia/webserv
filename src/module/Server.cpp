
#include <iostream>
#include "color.hpp"


#include "Server.hpp"

#define SEVER_NAME_HANDLER(structName, name, nb) \
	static Server::C_ServerSpec	structName(#name, &Server::name##_Handler, nb)

typedef	std::map<C_Str, Server::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

SEVER_NAME_HANDLER(NAME, server_name, 1);
SEVER_NAME_HANDLER(HOST, host, 1);
SEVER_NAME_HANDLER(PORT, port, 1);
SEVER_NAME_HANDLER(LISTEN, listen, 1);
static Server::C_ServerSpec EMPTY("empty", NULL, 0);

static Server::C_ServerSpec	SERVER_HANDLER[] = {
	NAME, HOST, PORT, LISTEN, EMPTY
};

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; SERVER_HANDLER[i]._handler != NULL; ++i)
		map[SERVER_HANDLER[i]._name] = SERVER_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	SEVER_MAP = buildMap();

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Server::Server(void): Core(Block::SERVER) {}

/* Destructor */
Server::~Server() {}

/* Getters */
std::vector<Location>	&Server::getLocations(void) {
	return (_locations);
}

/* Setters */
void	Server::addLocation(void) {
	_locations.push_back(Location());
	_locations.back().setRoot("Some Location!");
	std::cout << YLW "On server {" << _server_name << "}, added: " << _locations.back().getRoot() <<  RENDL;
}

/* Member Functions */
void		Server::setServerName(C_Str &name) {_server_name = name; }
std::string	Server::getServerName(void) { return (_server_name); }

/* Handlers */
Server::HandlerPointer	Server::selectHandler(C_Str &name) {
	DirectiveConst_it	it = SEVER_MAP.find(name);
	DirectiveConst_it	end = SEVER_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Server::server_name_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	_server_name = args.front();
	checkArgs(parser, NAME, outerBlock, args);

}

void	Server::host_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, HOST, outerBlock, args);
}

void	Server::port_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, PORT, outerBlock, args);
}

void	Server::listen_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, LISTEN, outerBlock, args);
}
