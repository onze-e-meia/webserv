


#ifndef MODULE_DEF_HPP
# define MODULE_DEF_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "color.hpp"

namespace Name {
	const std::string	LOCATION = "location";
	const std::string	SERVER = "server";
	const std::string	HTTP = "http";
	const std::string	CORE = "core";
	const std::string	EMPTY = "";
} // NAME

namespace Module {
	enum module_e {
		LOCATION = 0,
		SERVER,
		HTTP,
		CORE,
		EMPTY,
		SIZE,
	};
} // Module;

typedef std::bitset<Module::SIZE>	BlockType;

#endif // MODULE_DEF_HPP
