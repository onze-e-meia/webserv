

#include <iostream>


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

	Webserv(void);
	Webserv(const Webserv&);
	Webserv	&operator=(const Webserv&);

	static Webserv	&instance(void);

public:
	~Webserv(void) {};

	/* Getters */
	static char				*getPath(void);
	static std::ifstream	&getFile(void);

	/* Setters */
	static void	addBlock(Block::type_e &block);

	/* Member Functions */
	static void	checkPath(int argc, char **argv);
	static void	buildConfig(void);
	static void run(void);
	static int	close(void);

	/* Handlers */
	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);

	template <typename Class, typename HandlerPointer>
	static void	tyrHandler(Block::type_e block, ConstStr &name, ConstVecStr &args, Class &obj) {
		Core::HandlerPointer coreMethod = Core::selectHandler(name);
		if (coreMethod != NULL) {
			std::cout << GRN TAB "In " BLU << Block::getName(block) << GRN " found CORE directive: " TAB << name << RENDL;
			(obj.*coreMethod)(name, args, 11, 22);
			return ;
		}

		HandlerPointer	objMethod = Class::selectHandler(name);
		if (objMethod != NULL) {
			std::cout << GRN TAB "In " BLU << Block::getName(block) << GRN " found OBJ directive : " TAB << name << RENDL;
			(obj.*objMethod)(name, args, 11, 22);
			return ;
		}
		std::cout << RED TAB "In " BLU << Block::getName(block) << RED " UNKNOW directive: " TAB << name << RENDL;
		return ;
	}
};

#endif		// WERSERV_HPP
