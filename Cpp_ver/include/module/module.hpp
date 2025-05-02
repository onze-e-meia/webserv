
#ifndef MODULE_HPP
# define MODULE_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "module_def.hpp"

#define BLOCK_SPEC(name) { Name::name, name }

// Need this?
// #define BLOCK_FLAGS(name) (BlockType().set(Module::CORE).set(Module::name))

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

		// Spec(const std::string &name, Module::module_e module);
		// const BlockType	makeBlockFlags(Module::module_e module);
	}; // Spec

	const Spec	SPECS[] = {
		BLOCK_SPEC(LOCATION),
		BLOCK_SPEC(SERVER),
		BLOCK_SPEC(HTTP),
	};

	const SpecMap	build(void);
	BlockType		getType(std::string name);
	// BlockType		dispatch(std::string block);
} // Block

#endif // MODULE_HPP
