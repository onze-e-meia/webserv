




#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include "checkPath.hpp"
#include "Parser.hpp"
#include "Webserv.hpp"
#include "color.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

Webserv::status	Webserv::_status(0);
std::string		Webserv::_path("");
std::ifstream	*Webserv::_file = NULL;


/* Contsructor */
Webserv::Webserv(void): _http(Http()) {}

void	Webserv::addPath(ConstStr &path) {
	_path = path;
}

Webserv	&Webserv::instance(void) {
	static Webserv *webserv;

	if (_status.test(INSTANCE)) {
		return (*webserv);
	} else if (_status.test(PATH)) {
		webserv = new Webserv();
		_status.set(INSTANCE);
		return (*webserv);
	}
	throw (std::runtime_error("Unexpected error! Where?\n")); // TODO: Need this? Better message?
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Destructor */
Webserv::~Webserv() {}

/* Member Functions */
void	Webserv::checkPath(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path>\n";
		_status.set(FAIL);
		return ;
	}

	char	*path = argv[1];
	// if (!exists(path)) {
	// 	std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
	// 	return EXIT_FAILURE;
	// }
	if (isDirectory(path)) {
		std::cerr << "webserv Error: " << path << ": Is a directory\n";
		if (!isRead(path))
			std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
		_status.set(FAIL);
		return ;
	}

	std::ifstream *configFile = new std::ifstream(path);
	if (!(*configFile).is_open()) {
		std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
		_status.set(FAIL);
		delete configFile;
		return ;
	}
	addPath(path);
	_file = configFile;
	_status.set(PATH);
}

void	Webserv::buildConfig(void) {
	if (_status.test(PATH) == false) {
		std::cerr << "webserv Error: " << _path << ": Invalid PATH" ENDL;
		return ;
	}

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		Parser(*_file).parseConfigFile();
		_status.set(CONFING);
		// Logger	log("some_name.txt");
	} catch (const std::exception &exception) {
		_status.set(FAIL);
		std::cerr << RED " >>> HHHHAAAAALLLLTTTT!!!! <<< " RENDL;
		std::cerr << _path << ":" << exception.what();
	}
	// std::cout << "Servers Name: " ENDL
	// 	<< "PATH: " << _path << ENDL
	// 	<< instance()._http.getServers()[0].getName() << ENDL
	// 	<< instance()._http.getServers()[1].getName() << ENDL
	// 	<< instance()._http.getServers()[2].getName() << ENDL;
}

void Webserv::run(void) {
	std::cout << ENDL
		<< "*------------------*" ENDL
		<< "| Webserb  Running |" ENDL
		<< "*------------------*" ENDL;

}

int	Webserv::close(void) {
	if (_status.test(PATH)) {
		(*_file).close();
		delete _file;
	}
	if (_status.test(INSTANCE))
		delete &instance();

	std::cout << ENDL
		<< "*------------------*" ENDL
		<< "| Clossing Webserb |" ENDL
		<< "*------------------*" ENDL;
	return EXIT_SUCCESS;
}

void	Webserv::addBlock(Block::type_e &block) {
	if (block == Block::SERVER) {
		instance()._http.addServer();
	}
	if (block == Block::LOCATION) {
		// webserv._http.getServers().back()._locations;
		instance()._http.addLocation();
	}
}

void	Webserv::dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &args) {
	// const Module::module_e	MODULES[] = {
	// 	Module::CORE, Module::HTTP, Module::SERVER, Module::LOCATION, Module::EMPTY
	// };
	Http	&http = instance()._http;

	// for (std::size_t i = 0; MODULES[i] != 1; ++i) {
	// 	if (block & MODULES[i]) {

	// 	}

	// }
	CoreHandlerTemplate<Core, Core::HandlerPointer> CoreDef;
	tryHandle<CoreHandlerTemplate<Core, Core::HandlerPointer> >(block, name, args);

	// tryHandle<CoreHandler>(block, name, args);


	if (block & Module::CORE) { // CORE, all blocks have CORE
		// Core::HandlerPointer	method = callHandler<Core, Core::HandlerPointer>(name);
		// if (method != NULL) {
		// 	std::cout << GRN TAB ">>>> On CORE module Found: " TAB << name << RENDL;
		// 	(http.*method)(name, args, 11, 22);
		// 	return ;
		// }
		// callHandlerX<Core, Core::HandlerPointer>(block, name, args);

	}
	if (block == Block::HTTP) {
		Http::HandlerPointer	method = callHandler<Http, Http::HandlerPointer>(name);
		if (method != NULL) {
			std::cout << GRN TAB ">>>> On HTTP module Found: " TAB << name << RENDL;
			(http.*method)(name, args, 11, 22);
			return ;
		}
	}
	if (block == Block::SERVER) {
		Server::HandlerPointer	method = callHandler<Server, Server::HandlerPointer>(name);
		if (method != NULL) {
			std::cout << GRN TAB ">>>> On SERVER Found: " TAB << name << args[0] << RENDL;
			(http.getServers().back().*method)(name, args, 11, 22);
			std::cout << GRN TAB ">>>> SERVER NAME: " TAB << http.getServers().back().getName() << RENDL;
			return ;
		}
	}
	// std::cout << RED TAB ">>>> UNKNOW DIRETIVE!!!! " TAB << name << RENDL;
}
