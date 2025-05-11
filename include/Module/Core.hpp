




#ifndef		CORE_HPP
# define	CORE_HPP

# include <string>
# include <bitset>

# include <vector>
# include <map>
# include <set>
# include "Module.hpp"

typedef const std::string				ConstStr;
typedef const std::vector<std::string>	ConstVecStr;

template <typename HandlerPointer>
struct NameHandler {
	ConstStr		_name;
	HandlerPointer	_handler;
};

class Core {
public:
	typedef void	(Core::*HandlerPointer)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

protected:
	const Block::Module					_blockType;
	std::string							_root;
	std::set<std::string>				_index;
	std::bitset<1>						_autoindex;
	std::map<std::string, std::string>	_error_page;
	std::size_t							_client_max_body_size;
	std::set<std::string>				_allow_methods; // limit_except

public:
	/* Contsructor */
	Core(const Block::Module &block);

	/* Destructor */
	virtual ~Core(void);

	Block::Module	getBlockType(void) const { return (_blockType); }

	std::string		getRoot(void) const { return (_root); }
	void			setRoot(ConstStr root) { _root = root; }


	/* Handlers */
	static HandlerPointer	selectHandler(ConstStr &name);
	void	root_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	index_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	autoindex_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	error_page_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	client_max_body_size_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	allow_methods_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

#endif		// CORE_HPP
