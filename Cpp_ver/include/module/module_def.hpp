




#ifndef MODULE_DEF_HPP
# define MODULE_DEF_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "color.hpp"

namespace Name {
	const std::string	UNKNOW = "unknow";
	const std::string	EMPTY = "";
	const std::string	CORE = "core";
	const std::string	HTTP = "http";
	const std::string	SERVER = "server";
	const std::string	LOCATION = "location";
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

typedef int	BlockType; // REMOVE THIS, CHECK INCLUDES

#endif // MODULE_DEF_HPP

// struct FileAccess {
//     unsigned read    : 1;
//     unsigned write   : 1;
//     unsigned execute : 1;
//     unsigned delete_ : 1;
// };

// struct PackedAccess {
//     unsigned permissions : 4;
// };

// PackedAccess admin;
// admin.permissions = READ | WRITE | EXECUTE | DELETE;

// if (admin.permissions & READ)
//     std::cout << "Admin can read.\n";
