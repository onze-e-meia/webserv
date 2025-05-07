




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

class	Mime {}; // Class? Struct? What? Where?

class	Http: public	Core {
public:
	typedef void	(Http::*Handler)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

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

	// Http(const Http &http);
	Http	&operator=(const Http &other);

	static Http	&instance(void);
	std::string	getRoot() const;

	void	addServer(void);
	void	addLocation(void);

public:
	Http(void);
	~Http(void);

	// static const DirectiveMap	buildMap(void);
	static const Handler	selectHandler(ConstStr &name);

	std::vector<Server>	getServerS(void) { return (_servers); }
	Server	getServer(void) { return (_servers.back()); }

	static void	buildConfig(std::ifstream &file);
	static void	addBlock(Block::type_e &block);
	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);


	/* Handlers */
	void	mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

#endif		// HTTP_HPP
