

#include <iostream>


#include "module_def.hpp"
#include "config_parser.hpp"
#include "Http.hpp"

#include "color.hpp"

Http::status	Http::_status(0);

Http::Http(void): Core(Name::HTTP) {}
Http &Http::operator=(const Http &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

Http	&Http::instance(void) {
	if (_status.test(INSTANCE)) {
		std::ostringstream	oss;
		oss << H_BLU "Web Serve already instantiated\n" RST;
		throw (std::runtime_error(oss.str()));
	}
	_status.set(INSTANCE);
	static Http	instance;
	return (instance);
}

void	Http::buildConfig(std::ifstream &file) {
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
	// All InitError, LogicError, etc., inherit from MainModule::Exception, so you can:
	// catch (const MainModule::Exception& e) { /* fallback */ }
}



// Http		Http::getHttp(void) {
// 	return (*this);
// }

std::string	Http::getRoot() const {
	return (_root);
};

Http::~Http() {}
