
#include <iostream>
#include "color.hpp"


#include "Server.hpp"

// #define SEVER_NAME_HANDLER(name) { #name, &Server::name##_Handler }

#define SEVER_NAME_HANDLER(structName, name, nb) \
	const NameHandler<Server::HandlerPointer> structName(#name, &Server::name##_Handler, nb)

typedef	std::map<ConstStr, Server::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

SEVER_NAME_HANDLER(NAME, server_name, 1);
SEVER_NAME_HANDLER(HOST, host, 1);
SEVER_NAME_HANDLER(PORT, port, 1);
SEVER_NAME_HANDLER(LISTEN, listen, 1);
const NameHandler<Server::HandlerPointer> EMPTY("empty", NULL, 0);

static const NameHandler<Server::HandlerPointer>	SERVER_HANDLER[] = {
	NAME, HOST, PORT, LISTEN, EMPTY
};

// static const NameHandler<Server::HandlerPointer>	SERVER_HANDLER[] = {
// 	SEVER_NAME_HANDLER(server_name),
// 	SEVER_NAME_HANDLER(host),
// 	SEVER_NAME_HANDLER(port),
// 	SEVER_NAME_HANDLER(listen),
// 	{ "", NULL },
// };

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
void		Server::setServerName(ConstStr &name) {_server_name = name; }
std::string	Server::getServerName(void) { return (_server_name); }

/* Handlers */
Server::HandlerPointer	Server::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = SEVER_MAP.find(name);
	DirectiveConst_it	end = SEVER_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Server::server_name_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
	_server_name = args.front();
}

void	Server::host_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Server::port_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Server::listen_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}
