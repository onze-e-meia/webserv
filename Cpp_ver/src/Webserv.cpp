




#include <iostream>
#include <sstream>
#include "Parser.hpp"
#include "Webserv.hpp"
#include "color.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

Webserv::status	Webserv::_status(0);

/* Contsructor */
Webserv::Webserv(void): _http(Http()) {}

/* Destructor */
Webserv::~Webserv() {}

Webserv &Webserv::operator=(const Webserv &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

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

void	Webserv::addServer(void) {
	_http.getServerS().push_back(Server());
	// _http.addServer();
	// _http._servers.push_back(Server());
}

void	Webserv::addLocation(void) {
	// _http._servers.back();
	std::cout << YLW "LOCATION ADDED TO SERVER" RENDL;
}

// =============================================================================
// PUBLIC
// =============================================================================
void	Webserv::buildConfig(std::ifstream &file) {
	std::string	path = "src/somefile";

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		// Parser	parse(file);
		// parse.parseConfigFile();
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
	// http._servers[0].setName("Some name! 0 ");
	// http._servers[1].setName("Some name! 1 ");
	// http._servers[2].setName("Some name! 2 ");
	// std::cout << "Servers Name: " ENDL
	// 	<< http._servers[0].getName() << ENDL
	// 	<< http._servers[1].getName() << ENDL
	// 	<< http._servers[2].getName() << ENDL;
}

void	Webserv::addBlock(Block::type_e &block) {
	Webserv	&webserv = Webserv::instance();

	Server	sever = webserv._http.getServer();

	webserv._http.addBlock(block);

	if (block == Block::SERVER) {
		webserv.addServer();
		// webserv._http.addServer();
		// http._servers.push_back(Server());
	}
	if (block == Block::LOCATION) {
		webserv.addLocation();
	}

	Server::Handler	method;

	std::string	name;
	std::vector<std::string>	args;

	(webserv._http.getServerS().back().*method)(name, args, 1, 2);

}
