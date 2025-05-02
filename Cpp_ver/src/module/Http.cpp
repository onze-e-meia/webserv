

#include <iostream>


#include "module.hpp"
#include "config_parser.hpp"
#include "Http.hpp"

#include "color.hpp"

Http::status	Http::_status(0);

Http::Http(void): Core(Block::HTTP) {}

Http &Http::operator=(const Http &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

Http	&Http::instance(void) {
	// if (_status.test(INSTANCE)) {
	// 	std::ostringstream	oss;
	// 	oss << H_BLU "Web Serve already instantiated\n" RST;
	// 	throw (std::runtime_error(oss.str()));
	// }
	_status.set(INSTANCE);
	static Http	instance;
	return (instance);
}

void	Http::addServer(void) {
	_servers.push_back(Server());

	std::cout << YLW "SERVER ADDED TO HTTP " << _servers.back().getBlockType()  << RENDL;
	// std::cout << YLW "SERVER ADDED TO HTTP " << _servers[0].getBlockType() << RENDL;
}

void	Http::addLocation(void) {
	_servers.back();

	std::cout << YLW "LOCATION ADDED TO SERVER" RENDL;
}


void	Http::buildConfig(std::ifstream &file) {
	// std::cout
	// 	<< "TYPES" ENDL
	// 	// << Block::getType(Name::EMPTY) << ENDL
	// 	// << Block::getType(Name::CORE) << ENDL
	// 	<< Block::getType(Name::HTTP) << ENDL
	// 	<< Block::getType(Name::SERVER) << ENDL
	// 	<< Block::getType(Name::LOCATION) << ENDL
	// 	<< "END" ENDL;

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		Http	&http = Http::instance();
		std::cout << "DIRECTIVE NAME: " << http._root << "\n";
		parse(file);
		_status.set(CONFING);
		// Logger	log("some_name.txt");
		// _status = EXIT_SUCCESS;
	} catch (std::exception &exception) {
		_status.set(FAIL);
		std::cerr << "HHHHAAAAALLLLTTTT!!!!\n";
		std::cerr << exception.what();
	}

	// Http	&http = Http::instance();
	// http._servers[0].setName("Some name! 0 ");
	// http._servers[1].setName("Some name! 1 ");
	// http._servers[2].setName("Some name! 2 ");
	// std::cout << "Servers Name: " ENDL
	// 	<< http._servers[0].getName() << ENDL
	// 	<< http._servers[1].getName() << ENDL
	// 	<< http._servers[2].getName() << ENDL;

	// All InitError, LogicError, etc., inherit from MainModule::Exception, so you can:
	// catch (const MainModule::Exception& e) { /* fallback */ }
}

void	Http::addBlock(const BlockType &block) {
	Http	&http = Http::instance();

	if (block == Block::SERVER) {
		http.addServer();
	}
	if (block == Block::LOCATION) {
		http.addLocation();
	}
}

// Http		Http::getHttp(void) {
// 	return (*this);
// }

std::string	Http::getRoot() const {
	return (_root);
};

Http::~Http() {}
