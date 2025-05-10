




#ifndef		MODULE_HPP
# define	MODULE_HPP

# include <string>

namespace Name {
	const std::string	EMPTY		= "";
	const std::string	HTTP		= "http";
	const std::string	SERVER		= "server";
	const std::string	LOCATION	= "location";
	const std::string	CORE		= "core";
}

namespace Module {
	enum module_e {
		EMPTY		= 0x00,
		HTTP		= 0x01,
		SERVER		= 0x02,
		LOCATION	= 0x04,
		CORE		= 0x08,
	};
}

namespace Block { // BitMask to allowed blocks order.
	enum type_e {
		EMPTY		= ( Module::EMPTY ),
		HTTP		= ( Module::HTTP | Module::CORE ),
		SERVER		= ( Module::SERVER | Module::CORE ),
		LOCATION	= ( Module::LOCATION | Module::CORE ),
	};

	struct Spec{
		const std::string	_name;
		const type_e		_type;
	};

	type_e		dispatchType(const std::string &name);
	std::string	getName(type_e block);
}

class NewBlock {
private:
	unsigned	_module	: 4;
	unsigned	_mask	: 4;

public:
	NewBlock(unsigned module, unsigned mask): _module(module), _mask(mask) {};

	~NewBlock();
};

// NewBlock	http(Module::HTTP, Module::HTTP);

#endif		// MODULE_HPP
