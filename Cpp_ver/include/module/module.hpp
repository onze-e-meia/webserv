




#ifndef MODULE_HPP
# define MODULE_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "module_def.hpp"

#define BLOCK_SPEC(name) { Name::name, name }

namespace Block {
	enum block_e {
		EMPTY		= Module::EMPTY,
		HTTP		= ( Module::CORE | Module::HTTP ),
		SERVER		= ( Module::CORE | Module::SERVER ),
		LOCATION	= ( Module::CORE | Module::LOCATION ),
	};

	typedef std::map<const std::string, BlockType>	SpecMap;
	typedef SpecMap::const_iterator					SpecConst_it;

	extern const SpecMap	MAP;

	struct Spec{
		const std::string	_name;
		const BlockType		_type;
	};

	const Spec	SPECS[] = {
		BLOCK_SPEC(LOCATION),
		BLOCK_SPEC(SERVER),
		BLOCK_SPEC(HTTP),
	};

	// const SpecMap	build(void);
	BlockType		getType(std::string name);
	std::string		getName(BlockType block);
	// BlockType	dispatch(std::string block);
} // Block

#endif // MODULE_HPP
