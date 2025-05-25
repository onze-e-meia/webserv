




#include <iostream>
#include <sstream>

// #include "Parser.hpp"
#include "Http.hpp"

#include "color.hpp"

#define HTTP_NAME_HANDLER(structName, name, nb) \
	static Http::C_HttpSpec	structName(#name, &Http::name##_Handler, nb)

// const HandlerSpec<Http::HandlerPointer>	structName(#name, &Http::name##_Handler, nb)

typedef	std::map<C_Str, Http::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

HTTP_NAME_HANDLER(MIME, mime, 1);
HTTP_NAME_HANDLER(INCLUDE, include, 1);
static Http::C_HttpSpec EMPTY("empty", NULL, 0);

static Http::C_HttpSpec	HTTP_HANDLER[] = {
	MIME, INCLUDE, EMPTY
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
Http::HandlerPointer	Http::selectHandler(C_Str &name) {
	DirectiveConst_it	it = HTTP_MAP.find(name);
	DirectiveConst_it	end = HTTP_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Http::mime_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, MIME, outerBlock, args);
}

void	Http::include_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, INCLUDE, outerBlock, args);
	// std::cout << GRN TAB "CALL INCLUDE HANDLER Founs: " TAB << name << line << pos << RENDL;
}
