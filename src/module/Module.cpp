




#include <map>
#include "Module.hpp"

#define BLOCK_SPEC(name) { Name::name, Block::name }

typedef std::map<const std::string, Block::type_e>	SpecMap;
typedef SpecMap::const_iterator						SpecConst_it;

static const SpecMap	build(void) {
	const Block::Spec	SPECS[] = {
		BLOCK_SPEC(HTTP),
		BLOCK_SPEC(SERVER),
		BLOCK_SPEC(LOCATION),
		BLOCK_SPEC(EMPTY),
	};

	SpecMap	map;
	for (std::size_t i = 0; SPECS[i]._type != Block::EMPTY; ++i)
		map[SPECS[i]._name] = SPECS[i]._type;
	return (map);
}

static const SpecMap	BLOCK_MAP = build();

Block::type_e	Block::dispatchType(const std::string &name) {
	SpecConst_it	it = BLOCK_MAP.find(name);
	SpecConst_it	end = BLOCK_MAP.end();
	if (it == end)
		return (Block::EMPTY);
	return (it->second);
}

std::string	Block::getName(type_e block) { // TODO: Use map
	std::string	name;
	switch (block) {
		case HTTP:		return (Name::HTTP);
		case SERVER:	return (Name::SERVER);
		case LOCATION:	return (Name::LOCATION);
		default:		return (Name::EMPTY);
	}
}
