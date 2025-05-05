




#include "Location.hpp"

#define LOCATION_NAME_HANDLER(name) { #name, static_cast<handler_t>(&Location::name##_Handler) }

static const NameHandler	LOCATION_HANDLER[] = {
	LOCATION_NAME_HANDLER(some_location),
	{ "", NULL },
};

static const DirectiveMap	LOCATION_MAP = Location::buildMap();

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Location::Location(void): Core(Block::LOCATION) {
	// std::cout << YLW "Location ADDED TO HTTP " << _blockType  << RENDL;
}

/* Member Functions */
const DirectiveMap	Location::buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; LOCATION_HANDLER[i]._handler != NULL; ++i)
		map[LOCATION_HANDLER[i]._name] = LOCATION_HANDLER[i]._handler;
	return (map);
}

const handler_t	Location::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = LOCATION_MAP.find(name);
	DirectiveConst_it	end = LOCATION_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

/* Handlers */
void	Location::some_location_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}
