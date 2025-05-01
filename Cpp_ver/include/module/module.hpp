
#ifndef MODULE_HPP
# define MODULE_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "module_def.hpp"

#define BLOCK_SPEC(name) Spec(Name::name, Module::name)

// Need this?
#define BLOCK_FLAGS(name) (BlockType().set(Module::CORE).set(Module::name))

namespace Block {
	typedef std::map<const std::string, BlockType>	SpecMap;
	typedef SpecMap::const_iterator					SpecConst_it;

	extern const SpecMap	MAP;

	struct Spec{
		const std::string	_name;
		const BlockType		_type;

		Spec(const std::string &name, Module::module_e module);
		const BlockType	makeBlockFlags(Module::module_e module);
	}; // Spec

	const Spec	SPECS[] = {
		BLOCK_SPEC(LOCATION),
		BLOCK_SPEC(SERVER),
		BLOCK_SPEC(HTTP),
		BLOCK_SPEC(CORE),
		BLOCK_SPEC(EMPTY),
	};

	const SpecMap	build(void);
	BlockType		getType(std::string name);
	// BlockType		dispatch(std::string block);
} // Block

#endif // MODULE_HPP
