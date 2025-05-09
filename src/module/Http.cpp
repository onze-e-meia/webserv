




#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Http.hpp"

#include "color.hpp"

#define HTTP_NAME_HANDLER(name) { #name, &Http::name##_Handler }

typedef	std::map<ConstStr, Http::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

static const NameHandler<Http::HandlerPointer>	HTTP_HANDLER[] = {
	HTTP_NAME_HANDLER(mime),
	HTTP_NAME_HANDLER(include),
	{ "", NULL },
};

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; HTTP_HANDLER[i]._handler != NULL; ++i)
		map[HTTP_HANDLER[i]._name] = HTTP_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	HTTP_MAP = buildMap();

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Http::Http(void): Core(Block::HTTP) {}

/* Destructor */
Http::~Http() {}

/* Getters */
std::vector<Server>	&Http::getServers(void) {
	 return (_servers);
}

/* Setters */
void	Http::addServer(void) {
	_servers.push_back(Server());
	_servers.back().setServerName("TESTE XXX");
	std::cout << YLW "server {" << _servers.back().getServerName() << "} added tp http" RENDL;
}

/* Member Functions */


/* Handlers */
Http::HandlerPointer	Http::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = HTTP_MAP.find(name);
	DirectiveConst_it	end = HTTP_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Http::mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
}

void	Http::include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	(void)name; (void)args; (void)line; (void)pos; // TODO: Fix, complete delete.
	// std::cout << GRN TAB "CALL INCLUDE HANDLER Founs: " TAB << name << line << pos << RENDL;
}
