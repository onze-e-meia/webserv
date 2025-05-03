



#ifndef		HTTP_HPP
# define	HTTP_HPP

# include <bitset>
# include <string>
# include <sstream>

# include <map>
# include <set>
# include <vector>
# include <exception>

# include "Logger.hpp"
# include "Core.hpp"
# include "Server.hpp"
// #include "config_directives.hpp"

class	Token;
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

	// Http		getHttp(void);
	static Http	&instance(void);
	std::string	getRoot() const;

	void	addServer(void);
	void	addLocation(void);

public:
	~Http(void);

	static void	buildConfig(std::ifstream &file);
	static void	addBlock(const BlockType &block);

	class	Exception;
	class	EmptyBlock;
	class	WrongBlock;
};

# include "Exception.hpp"

// class Http::Exception {

// };

#endif		// HTTP_HPP
