




#include <iostream>
#include <sstream>
#include "Parser.hpp"
#include "Webserv.hpp"
#include "color.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

Webserv::status	Webserv::_status(0);

std::string	Webserv::_path("");

/* Contsructor */
Webserv::Webserv(void): _http(Http()) {}

Webserv::Webserv(ConstStr &path): _http(Http()) {
	_path = path;
}

void	Webserv::addPath(ConstStr &path) {
	_path = path;
}


/* Destructor */
Webserv::~Webserv() {}

Webserv &Webserv::operator=(const Webserv &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

// void	Webserv::addPath(ConstStr &path) {
// 	instance()._path = path;
// }


Webserv	&Webserv::instance(void) {
	// if (_status.test(INSTANCE)) {
	// 	std::ostringstream	oss;
	// 	oss << H_BLU "Web Serve already instantiated\n" RST;
	// 	throw (std::runtime_error(oss.str()));
	// }
	_status.set(INSTANCE);
	static Webserv	instance;
	return (instance);
}

// void	Webserv::addServer(void) {
// 	_http.getServers().push_back(Server());
// }

// void	Webserv::addLocation(void) {
// 	_http.getServers().back();
// 	std::cout << YLW "LOCATION ADDED TO SERVER" RENDL;
// }

// =============================================================================
// PUBLIC
// =============================================================================
void	Webserv::buildConfig(std::ifstream &file) {
	std::string	path = "src/config/config_file";

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		// Parser	parse(file);
		// parse.parseConfigFile();
		Webserv::addPath(path);
		Parser(file).parseConfigFile();
		_status.set(CONFING);
		// Logger	log("some_name.txt");
		// _status = EXIT_SUCCESS;
	} catch (const std::exception &exception) {
		_status.set(FAIL);
		std::cerr << RED " >>> HHHHAAAAALLLLTTTT!!!! <<< " RENDL;
		std::cerr << path << ":" << exception.what();
	}
	Webserv	&webserv = Webserv::instance();
	std::cout << "Servers Name: " ENDL
		<< "PATH: " << Webserv::_path << ENDL
		<< instance()._http.getServers()[0].getName() << ENDL
		<< instance()._http.getServers()[1].getName() << ENDL
		<< instance()._http.getServers()[2].getName() << ENDL;
}

void	Webserv::addBlock(Block::type_e &block) {
	// Webserv	&webserv = instance();

	if (block == Block::SERVER) {
		instance()._http.addServer();
	}
	if (block == Block::LOCATION) {
		// webserv._http.getServers().back()._locations;
		instance()._http.addLocation();
	}
}

void	Webserv::dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec) {
	Http	&http = instance()._http;

	if (true) { // CORE, all blocks have CORE
		Core::Handler	method = callHandler<Core, Core::Handler>(name);
		if (method) {
			std::cout << GRN TAB ">>>> On CORE module Found: " TAB << name << RENDL;
			(http.*method)(name, vec, 11, 22);
			return ;
		}
	}
	if (block == Block::HTTP) {
		Http::Handler	method = callHandler<Http, Http::Handler>(name);
		if (method) {
			std::cout << GRN TAB ">>>> On HTTP module Found: " TAB << name << RENDL;
			(http.*method)(name, vec, 11, 22);
			return ;
		}
	}
	if (block == Block::SERVER) {
		Server::Handler	method = callHandler<Server, Server::Handler>(name);
		if (method) {
			std::cout << GRN TAB ">>>> On SERVER Found: " TAB << name << vec[0] << RENDL;
			(http.getServers().back().*method)(name, vec, 11, 22);
			std::cout << GRN TAB ">>>> SERVER NAME: " TAB << http.getServers().back().getName() << RENDL;
			return ;
		}
	}
	std::cout << RED TAB ">>>> UNKNOW DIRETIVE!!!! " TAB << name << RENDL;
}
