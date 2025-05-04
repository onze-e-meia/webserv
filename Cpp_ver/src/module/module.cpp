



#include "module.hpp"
#include "color.hpp"

static const Block::SpecMap	build(void);

const Block::SpecMap	Block::MAP = build();

const Block::SpecMap	build(void) {
	std::cout << ">>>>>>>>>>>>>>>>>>>> BUILD MAP <<<<<<<<<<<<<<<< " << ENDL;
	Block::SpecMap	map;
	for (size_t i = 0; Block::SPECS[i]._type != 0; ++i)
		map[Block::SPECS[i]._name] = Block::SPECS[i]._type;
	return (map);
}

BlockType	Block::getType(std::string name) {
	SpecConst_it	it = MAP.find(name);
	SpecConst_it	end = MAP.end();
	if (it == end) {
		std::ostringstream oss;
		oss << RED " >>>>>>>>>> Unknown NEW block: " << name << RENDL;
		throw (std::runtime_error(oss.str()));
		// Make this return EMPTY, Remove unknow
	}
	return (it->second);
}

std::string	Block::getName(BlockType block) {
	std::string	name;
	switch (block) {
		case EMPTY:		return (Name::EMPTY);
		case HTTP:		return (Name::HTTP);
		case SERVER:	return (Name::SERVER);
		case LOCATION:	return (Name::LOCATION);
		default:		return (Name::UNKNOW);
	}
}
