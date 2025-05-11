




#include <map>
#include "Module.hpp"

#define BLOCK_MODULE(name) \
	const Module name(Name::name, name##_T, name##_BM)

namespace Block {
	typedef std::map<const std::string, Module>	SpecMap;
	typedef SpecMap::const_iterator				SpecConst_it;

	/* Contsructor */
	Module::Module(void):
	_name(""), _module(EMPTY_T), _mask(EMPTY_BM) {};

	Module::Module(const std::string &name, type_e module, bitMask_e mask):
	_name(name), _module(module), _mask(mask) {};

	/* Copy Assignment Contsructor */
	Module &Module::operator=(const Module &other) {
		if (this != &other) {
			_name = other._name;
			_module = other._module;
			_mask = other._mask;
		}
		return (*this);
	}

	/* Operator Overload*/
	bool	Block::Module::operator==(const Module &right) const {
		return ((_name == right._name) &&
				(_module == right._module) &&
				(_mask == right._mask));
	}

	/* Map of Blocks Types */
	BLOCK_MODULE(UNKNOWN);
	BLOCK_MODULE(LOCATION);
	BLOCK_MODULE(SERVER);
	BLOCK_MODULE(HTTP);
	BLOCK_MODULE(EMPTY);

	static const SpecMap	build(void) {
		const Module	BLOCKS[] = { LOCATION, SERVER, HTTP, EMPTY, };

		SpecMap	map;
		for (std::size_t i = 0; BLOCKS[i]._module != EMPTY._module; ++i)
			map[BLOCKS[i]._name] = BLOCKS[i];
		return (map);
	}

	static const SpecMap	BLOCK_MAP = build();

	/* Helper Functions */
	Module	dispatchType(const std::string &name) {
		SpecConst_it	it = BLOCK_MAP.find(name);
		SpecConst_it	end = BLOCK_MAP.end();
		if (it == end)
			return (UNKNOWN);
		return (it->second);
	}

	bool	validNbArgs(const Module &inner, const std::vector<std::string> &args) {
		return (
			(args.empty() && (inner._module & (HTTP._module | SERVER._module))) ||
			(args.size() == 1 && (inner._module & LOCATION._module))
		);
	}

	bool	validOrder(const Module &outer, const Module &inner) {
		return ((outer._mask & inner._module) >= 1);
	}
}
