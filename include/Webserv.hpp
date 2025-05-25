

#include <iostream>
#include <sstream>


#ifndef		WEBSERV_HPP
# define	WEBSERV_HPP

# include "Http.hpp"
# include "color.hpp"

class	Parser;

class	Webserv {
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
	static bool				checkInstance(void);

	/* Setters */
	static void	addBlock(Block::Module &block, C_VecStr &args);

	/* Member Functions */
	static void	checkPath(int argc, char **argv);
	static void	buildConfig(void);
	static void	run(void);
	static int	close(void);

	/* Handlers */
	static void	dispatchHandler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);

	template <typename Class>
	static typename Class::HandlerPointer	handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
		typename Class::HandlerPointer method = Core::selectHandler(directive);
		if (method != NULL) {
			std::cout << GRN TAB "In " BLU << outerBlock._name << GRN " found CORE directive: " TAB << directive << RENDL;
			return (method);
		}

		method = Class::selectHandler(directive);
		if (method != NULL) {
			std::cout << GRN TAB "In " BLU << outerBlock._name << GRN " found OBJ directive : " TAB << directive << RENDL;
			return (method);
		}
		throw (Core::UnknownDirective(parser, directive, outerBlock, args));
	}
};

#endif		// WERSERV_HPP
