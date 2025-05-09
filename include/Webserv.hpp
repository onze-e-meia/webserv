

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
	// static Webserv		*_webserv;
	static status			_status;
	static std::string		_path;
	static std::ifstream	*_file;
	Http					_http;
	// std::string			_access_log;
	// std::string			_error_log;

	Webserv(void);
	Webserv(const Webserv&);
	Webserv	&operator=(const Webserv&);

	static void		addPath(ConstStr &path);
	static Webserv	&instance(void);

public:
	~Webserv(void);

	static void	checkPath(int argc, char **argv);
	static void	buildConfig(void);
	static void run(void);
	static int	close(void);

	static void	addBlock(Block::type_e &block);

	/* Handlers */
	template <typename Class, typename HandlerPointer>
	static HandlerPointer	callHandler(ConstStr &name) {
		HandlerPointer	method = Class::selectHandler(name);
		if (method != NULL)
			return (method);
		return (NULL);
	}

	template <typename Class, typename HandlerPointer>
	struct typeDefs {
		typedef Class ClassType;
		typedef HandlerPointer HandlerType;
	};

	template <typename Class, typename HandlerPointer>
	static void	callHandlerX(Block::type_e block, ConstStr &name, ConstVecStr &args) {
		HandlerPointer	method = Class::selectHandler(name);
		if (method != NULL) {
			std::cout << GRN TAB "TEMPLATE >>>> On " << Block::getName(block) << " Block Found: " TAB << name << RENDL;
			(instance()._http.*method)(name, args, 11, 22);
		}
		// 	return (method);
		// return (NULL);
	}

	template <typename Class, typename HandlerPointer>
	struct CoreHandlerTemplate {
		typedef Class ClassType;
		typedef HandlerPointer HandlerType;
	};

	struct CoreHandler {
		typedef Core::HandlerPointer HandlerType;
		typedef Core ClassType;
	};

	template <typename Module>
	static bool tryHandle(Block::type_e block, ConstStr &name, ConstVecStr &args) {
		// if (block & instance()._http.Module::ClassType::getBlockType())
		// 	return false;

		// typename Module::HandlerType method = callHandler<typename Module::ClassType, typename Module::HandlerType>(name);
		typename Module::HandlerType method = Module::ClassType::selectHandler(name);
		if (method != NULL) {
			std::cout << BLU ">>>>>>>>>>>>>>>>>>>>>>>>> Found in module: " << name << std::endl;
			(instance()._http.*method)(name, args, 11, 22);
			return true;
		}
		return false;
	}

	static void	dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec);
};

#endif		// WERSERV_HPP
