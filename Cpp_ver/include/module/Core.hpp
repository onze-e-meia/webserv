




#ifndef		CORE_HPP
# define	CORE_HPP

# include <string>
# include <bitset>

# include <vector>
# include <map>
# include <set>
# include "module.hpp"

class Core;
typedef const std::string						ConstStr;
typedef const std::vector<std::string>			ConstVecStr;
typedef void	(Core::*handler_t)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);
typedef	std::map<const std::string, handler_t>	DirectiveMap;
typedef DirectiveMap::const_iterator			DirectiveConst_it;

struct NameHandler {
	const std::string	_name;
	handler_t			_handler;
};

class Core {
protected:
	const Block::type_e					_blockType;
	std::string							_root;
	std::set<std::string>				_index;
	std::bitset<1>						_autoindex;
	std::map<std::string, std::string>	_error_page;
	std::size_t							_client_max_body_size;
	std::set<std::string>				_allow_methods; // limit_except

public:
	Core(const Block::type_e &block);
	virtual ~Core(void);

	static const DirectiveMap	buildMap(void);
	static const handler_t		selectHandler(ConstStr &name);

	/* Handlers */
	void	root_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	index_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	autoIndex_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	error_page_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	client_max_body_size_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	allow_methods_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

// struct NameHandler{
// 	const std::string	_name;
// 	Core::handler_t			_handler;
// };


#endif		// CORE_HPP
