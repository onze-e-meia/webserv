




#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Http.hpp"

#include "color.hpp"

#define HTTP_NAME_HANDLER(name) { #name, &Http::name##_Handler }

typedef	std::map<ConstStr, Http::Handler>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

static const NameHandler<Http::Handler>	HTTP_HANDLER[] = {
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

Http::status	Http::_status(0);

/* Member Functions */
const Http::Handler	Http::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = HTTP_MAP.find(name);
	DirectiveConst_it	end = HTTP_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

Http	&Http::instance(void) {
	// if (_status.test(INSTANCE)) {
	// 	std::ostringstream	oss;
	// 	oss << H_BLU "Web Serve already instantiated\n" RST;
	// 	throw (std::runtime_error(oss.str()));
	// }
	_status.set(INSTANCE);
	static Http	instance;
	return (instance);
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Http::Http(void): Core(Block::HTTP) {}

Http &Http::operator=(const Http &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

/* Destructor */
Http::~Http() {}

/* Getters */
std::vector<Server>	&Http::getServers(void) {
	 return (_servers);
}

/* Member Functions */
void	Http::addServer(void) {
	_servers.push_back(Server());
}

void	Http::addLocation(void) {
	_servers.back();
	std::cout << YLW "LOCATION ADDED TO SERVER" RENDL;
}

/* Handlers */
void	Http::mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Http::include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	std::cout << GRN TAB "CALL INCLUDE HANDLER Founs: " TAB << name << line << pos << RENDL;
}
