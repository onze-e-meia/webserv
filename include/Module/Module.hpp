




#ifndef		MODULE_HPP
# define	MODULE_HPP

# include <string>

namespace Name { // TODO: CORE should be first!!
	const std::string	EMPTY		= "";
	const std::string	CORE		= "core";
	const std::string	HTTP		= "http";
	const std::string	SERVER		= "server";
	const std::string	LOCATION	= "location";
}

namespace Module {
	enum module_e {
		EMPTY		= 0x01,
		CORE		= 0x02,
		HTTP		= 0x04,
		SERVER		= 0x08,
		LOCATION	= 0x10,
	};
}

namespace Block { // TODO: Fix BitMask to include valid blocks inside
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

	type_e		dispatchType(const std::string &name);
	std::string	getName(type_e block);
}

#endif		// MODULE_HPP
