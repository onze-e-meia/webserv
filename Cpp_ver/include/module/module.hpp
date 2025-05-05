




#ifndef		MODULE_HPP
# define	MODULE_HPP

# include <string>
# include <map>
# include "module_def.hpp"

namespace Block {
	enum type_e {
		EMPTY		= ( Module::EMPTY ),
		HTTP		= ( Module::CORE | Module::HTTP ),
		SERVER		= ( Module::CORE | Module::SERVER ),
		LOCATION	= ( Module::CORE | Module::LOCATION ),
	};

	struct Spec{
		const std::string	_name;
		const type_e		_type;
	};

	type_e		getType(const std::string &name);
	std::string	getName(type_e block);
	// BlockType	dispatch(std::string block);
}

#endif		// MODULE_HPP
