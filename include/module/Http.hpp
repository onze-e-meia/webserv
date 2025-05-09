




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

class	Mime {}; // Class? Struct? What? Where?

class	Http: public	Core {
public:
	typedef void	(Http::*HandlerPointer)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

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
	std::vector<Server> _servers;
	Mime				_mime;
	std::string			_include;

public:
	Http(void);
	// Http(const Http &http);
	// Http	&operator=(const Http &other);
	~Http(void);

	std::vector<Server>	&getServers(void);

	void	addServer(void);
	void	addLocation(void);

	static HandlerPointer	selectHandler(ConstStr &name);

	/* Handlers */
	void	mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

#endif		// HTTP_HPP
