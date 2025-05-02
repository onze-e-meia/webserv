


#ifndef MODULE_DEF_HPP
# define MODULE_DEF_HPP

# include <bitset>
# include <iostream>
# include <map>

# include "color.hpp"

namespace Name {
	const std::string	EMPTY = "";
	const std::string	CORE = "core";
	const std::string	HTTP = "http";
	const std::string	SERVER = "server";
	const std::string	LOCATION = "location";
} // NAME

// SEND THIS TO HELL!!!!
namespace Module {
	enum module_e {
		EMPTY		= 0x01,
		CORE		= 0x02,
		HTTP		= 0x04,
		SERVER		= 0x08,
		LOCATION	= 0x10,
	};
} // Module;

typedef int	BlockType;

#endif // MODULE_DEF_HPP



/* AND ENUM THE HELL OUT OF THIS!!!!!
typedef int	directiveSet_e;
#define	INIT_D		0x01
#define CORE_D		0x02
#define HTTP_D		0X04
#define SERVER_D	0x08
#define LOCATION_D	0x16

typedef int	blockType_e;
#define BLOCK_INIT		INIT_D
#define BLOCK_HTTP		(CORE_D | HTTP_D)
#define BLOCK_SERVER	(CORE_D | SERVER_D)
#define BLOCK_LOCATION	(CORE_D | LOCATION_D)
 */

// enum	test_e {
// 	XINIT_D		= 0x01,
// 	XCORE_D		= 0x02,
// 	XHTTP_D		= 0X04,
// 	XSERVER_D	= 0x08,
// 	XLOCATION_D	= 0x10,
// 	XSIZE,
// };


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
