




#ifndef		TYPEDEF_HPP
# define	TYPEDEF_HPP

# include <string>
# include <vector>

class	Parser;
namespace	Block {
	struct	Module;
};

typedef const std::string				C_Str;
typedef const std::vector<std::string>	C_VecStr;
typedef const Parser					C_Parser;
typedef const Block::Module 			C_Block;

#endif		// TYPEDEF_HPP
