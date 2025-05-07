




#ifndef		WEBSERV_HPP
# define	WEBSERV_HPP

# include "Http.hpp"

class Webserv {
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
	static Webserv		*_webserv;
	static status		_status;
	static std::string	_path;
	Http				_http;
	// std::string			_access_log;
	// std::string			_error_log;

	Webserv(void);
	Webserv(const Webserv &other);
	Webserv	&operator=(const Webserv &other);

	static void		addPath(ConstStr &path);
	static Webserv	&instance(void);

public:
	~Webserv(void);

	static void	buildConfig(std::ifstream &file);
	static void	addBlock(Block::type_e &block);

	/* Handlers */
	template <typename Module, typename Handler>
	static Handler	callHandler(ConstStr &name) {
		Handler	method = Module::selectHandler(name);
		if (method != NULL)
			return (method);
		return (NULL);
	}
	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);
};

#endif		// WERSERV_HPP
