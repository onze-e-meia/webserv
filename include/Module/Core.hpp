




#ifndef		CORE_HPP
# define	CORE_HPP

# include <string>
# include <bitset>

# include <vector>
# include <map>
# include <set>
# include "typedef.hpp"
# include "Module.hpp"

template <typename HandlerPointer>
struct	HandlerSpec {
	C_Str			_name;
	HandlerPointer	_handler;
	std::size_t		_maxArgs;

	// HandlerSpec(void);
	HandlerSpec(C_Str &name, HandlerPointer handler, std::size_t maxArgs):
	_name(name), _handler(handler), _maxArgs(maxArgs) {}
};

class	Core {
public:
	typedef void	(Core::*HandlerPointer)(C_Parser&, C_Str&, C_Block&, C_VecStr&);
	typedef const HandlerSpec<Core::HandlerPointer>	C_CoreSpec;

protected:
	const Block::Module					_blockType;
	std::string							_root;
	std::set<std::string>				_index;
	std::bitset<1>						_autoindex;
	std::map<std::string, std::string>	_error_page;
	std::size_t							_client_max_body_size;
	std::set<std::string>				_allow_methods; // limit_except from nginx

	template<typename SpecStruct>
	static void checkArgs(C_Parser &parser, const SpecStruct &spec, C_Block &outerBlock, C_VecStr &args) {
		std::size_t nbArgs = args.size();
		if ((nbArgs == 0 || nbArgs > spec._maxArgs) ? true : false)
			throw (NumberArgs(parser, spec._name, outerBlock, args));
	}

public:
	/* Contsructor */
	Core(const Block::Module &block);

	/* Destructor */
	virtual ~Core(void);

	Block::Module	getBlockType(void) const { return (_blockType); }

	std::string		getRoot(void) const { return (_root); }
	void			setRoot(C_Str root) { _root = root; }

	/* Handlers */
	static HandlerPointer	selectHandler(C_Str &name);
	void	root_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	index_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	autoindex_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	error_page_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	client_max_body_size_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	allow_methods_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);

	/* Exception Classes */
	class	Exception;
	/* Parser Size Limits */
	class	UnknownDirective;
	class	NumberArgs;
	class	InvalidType;

};

# include "CoreExceptio.hpp"

#endif		// CORE_HPP
