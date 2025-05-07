




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
	static status		_status;
	Http				_http;
	// std::string			_access_log;
	// std::string			_error_log;

	Webserv(void);
	Webserv(const Webserv &other);
	Webserv	&operator=(const Webserv &other);

	static Webserv	&instance(void);
	std::string	getRoot() const;

	void	addServer(void);
	void	addLocation(void);

public:
	~Webserv(void);

	static void	buildConfig(std::ifstream &file);
	static void	addBlock(Block::type_e &block);
	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);

};



#endif		// WERSERV_HPP
