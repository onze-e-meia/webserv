




#ifndef		MODULE_HPP
# define	MODULE_HPP

# include <string>
# include <vector>

namespace Name {
	const std::string	UNKNOWN		= "unknown";
	const std::string	EMPTY		= "empty";
	const std::string	CORE		= "core";
	const std::string	LOCATION	= "location";
	const std::string	SERVER		= "server";
	const std::string	HTTP		= "http";
}

namespace Block {
	enum type_e { // Block type.
		UNKNOWN_T	= 0x00,
		EMPTY_T		= 0x01,
		CORE_T		= 0x02,
		LOCATION_T	= 0x04,
		SERVER_T	= 0x08,
		HTTP_T		= 0x10,
	};

	enum bitMask_e { // BitMask for allowed block type and order.
		UNKNOWN_BM	= ( UNKNOWN_T ),
		EMPTY_BM	= ( HTTP_T ),
		LOCATION_BM	= ( CORE_T ),
		SERVER_BM	= ( LOCATION_T | CORE_T ),
		HTTP_BM		= ( SERVER_T | CORE_T ),
	};

	struct Module {
		std::string	_name;
		type_e		_module;
		bitMask_e	_mask;

		/* Contsructor */
		Module(void);
		Module(const std::string &name, type_e module, bitMask_e mask);
		Module &operator=(const Module &other);

		/* Operator Overload*/
		bool	operator==(const Module &right) const;
	};

	/* Map of Blocks Types */
	const extern Module UNKNOWN;
	const extern Module EMPTY;
	const extern Module LOCATION;
	const extern Module SERVER;
	const extern Module HTTP;

	/* Helper Functions */
	Module	dispatchType(const std::string &name);
	bool	validNbArgs(const Module &inner, const std::vector<std::string> &args);
	bool	validOrder(const Module &outer, const Module &inner);
}

#endif		// MODULE_HPP
