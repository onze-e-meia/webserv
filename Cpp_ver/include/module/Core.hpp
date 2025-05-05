




#ifndef		CORE_HPP
# define	CORE_HPP

# include <string>
# include <bitset>

# include <map>
# include <set>
# include "module_def.hpp"

class Core {
protected:
	const BlockType						_blockType;
	std::string							_root;
	std::set<std::string>				_index;
	std::bitset<1>						_autoindex;
	std::map<std::string, std::string>	_error_page;
	std::size_t							_client_max_body_size;
	std::set<std::string>				_allow_methods; // limit_except

public:
	Core(const std::string &name);
	Core(const BlockType &block);
	virtual ~Core(void);
};



#endif		// CORE_HPP
