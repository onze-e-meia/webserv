




#include "Location.hpp"

#define LOCATION_NAME_HANDLER(structName, name, nb) \
	static Location::C_LocationSpec	structName(#name, &Location::name##_Handler, nb)

typedef	std::map<C_Str, Location::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator		DirectiveConst_it;

LOCATION_NAME_HANDLER(LOC_DRTCV, location_directive, 1);
static Location::C_LocationSpec EMPTY("empty", NULL, 0);

static Location::C_LocationSpec	LOCATION_HANDLER[] = {
	LOC_DRTCV, EMPTY
};

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; LOCATION_HANDLER[i]._handler != NULL; ++i)
		map[LOCATION_HANDLER[i]._name] = LOCATION_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	LOCATION_MAP = buildMap();

// =============================================================================
// PRIVATE
// =============================================================================

/* Member Functions */


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Location::Location(void): Core(Block::LOCATION) {}

/* Destructor */
Location::~Location() {}

/* Setters */
void	Location::setLocationPath(C_Str &path) {
	_locationPath = path;
}

/* Member Functions */


/* Handlers */
Location::HandlerPointer	Location::selectHandler(C_Str &name) {
	DirectiveConst_it	it = LOCATION_MAP.find(name);
	DirectiveConst_it	end = LOCATION_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Location::location_directive_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)parser; (void)directive; (void)outerBlock; (void)args; // TODO: Fix, complete delete.
	checkArgs(parser, LOC_DRTCV, outerBlock, args);

}
