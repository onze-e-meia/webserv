




#ifndef		HTTP_HPP
# define	HTTP_HPP

// # include <bitset>
# include <string>

# include <map>
# include <set>
# include <vector>
# include <exception>

# include "Core.hpp"
# include "Server.hpp"
// #include "config_directives.hpp"

class	Mime {};

class	Http: public	Core {
public:
	enum	status_e {
		INSTANCE = 0,
		CONFING,
		RUM,
		FAIL,
		SIZE,
	};

	typedef std::bitset<SIZE>	status;

private:
	static status		_status;
	std::vector<Server> _servers;
	Mime				_mime;
	std::string			_include;

	std::string				_access_log;
	std::string				_error_log;

	Http(void);
	Http(const Http &http);
	Http	&operator=(const Http &other);

	static Http	&instance(void);
	std::string	getRoot() const;

	void	addServer(void);
	void	addLocation(void);

public:
	~Http(void);

	static const DirectiveMap	buildMap(void);
	static const handler_t		selectHandler(ConstStr &name);

	static void	buildConfig(std::ifstream &file);
	static void	addBlock(Block::type_e &block);
	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);


	/* Handlers */
	void	mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

#endif		// HTTP_HPP
