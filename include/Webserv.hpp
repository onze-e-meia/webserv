

#include <iostream>
#include <sstream>


#ifndef		WEBSERV_HPP
# define	WEBSERV_HPP

# include "Http.hpp"
# include "color.hpp"

class Webserv {
public:
	enum	status_e {
			PATH = 0,
			INSTANCE,
			CONFING,
			RUM,
			FAIL,
			SIZE,
		};

	typedef std::bitset<SIZE>	status;

private:
	static status			_status;
	static char				*_path;
	static std::ifstream	*_file;
	Http					_http;

	// std::string			_access_log;
	// std::string			_error_log;

	/* Contsructor */
	Webserv(void);
	Webserv(const Webserv&);
	Webserv	&operator=(const Webserv&);

	static Webserv	&instance(void);

public:
	/* Destructor */
	~Webserv(void) {};

	/* Getters */
	static char				*getPath(void);
	static std::ifstream	&getFile(void);

	/* Setters */
	static void	addBlock(Block::Module &block, ConstVecStr &args);

	/* Member Functions */
	static void	checkPath(int argc, char **argv);
	static void	buildConfig(void);
	static void run(void);
	static int	close(void);

	/* Handlers */
	static void	dispatchHandler(Block::Module outerBlock, ConstStr &name, ConstVecStr &args);

	// TODO: Make handler set fail, so the exception can be handled outside the hpp
	template <typename Class, typename HandlerPointer>
	static HandlerPointer	handler(Block::Module outerBlock, ConstStr &name, ConstVecStr &args, Class &obj) {
		HandlerPointer method = Core::selectHandler(name);
		if (method != NULL) {
			std::cout << GRN TAB "In " BLU << outerBlock._name << GRN " found CORE directive: " TAB << name << RENDL;
			return (method);
		}

		method = Class::selectHandler(name);
		if (method != NULL) {
			std::cout << GRN TAB "In " BLU << outerBlock._name << GRN " found OBJ directive : " TAB << name << RENDL;
			return (method);
		}

		std::ostringstream	oss;
		oss << RED TAB "In " BLU << outerBlock._name << RED " UNKNOW directive: " TAB << name << RENDL;
		throw (std::runtime_error(oss.str()));
	}
};

#endif		// WERSERV_HPP
