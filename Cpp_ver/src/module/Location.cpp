




#include "Location.hpp"

#define LOCATION_NAME_HANDLER(name) { #name, &Location::name##_Handler }

typedef	std::map<ConstStr, Location::Handler>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

static const NameHandler<Location::Handler>	LOCATION_HANDLER[] = {
	LOCATION_NAME_HANDLER(some_location),
	{ "", NULL },
};

const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; LOCATION_HANDLER[i]._handler != NULL; ++i)
		map[LOCATION_HANDLER[i]._name] = LOCATION_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	LOCATION_MAP = buildMap();

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Location::Location(void): Core(Block::LOCATION) {
	// std::cout << YLW "Location ADDED TO HTTP " << _blockType  << RENDL;
}

/* Member Functions */
const Location::Handler	Location::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = LOCATION_MAP.find(name);
	DirectiveConst_it	end = LOCATION_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

/* Handlers */
void	Location::some_location_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}
