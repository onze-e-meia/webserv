




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
			std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << ENDL;
		_status.set(FAIL);
		return ;
	}

	std::ifstream *configFile = new std::ifstream(path);
	if (!(*configFile).is_open()) {
		std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << ENDL;
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
		{
			Http	http = instance()._http;
			http.getServers()[1].getLocations()[1].setRoot("Other Location");
			std::cout
				<< "PATH: " << _path << ENDL
				<< "First  Server Name: " << http.getServers()[0].getServerName() << ENDL
				<< "Second Server Name: " << http.getServers()[1].getServerName() << ENDL
				<< "Third  Server Name: " << http.getServers()[2].getServerName() << ENDL
				<< "   Location 1 Root: " << http.getServers()[1].getLocations()[0].getRoot() << ENDL
				<< "   Location 2 Root: " << http.getServers()[1].getLocations()[1].getRoot() << ENDL
				<< "   Location 3 Root: " << http.getServers()[1].getLocations()[2].getRoot() << ENDL;
		}
	} catch (const std::exception &exception) {
		_status.set(FAIL);
		std::cerr << RED " >>> HHHHAAAAALLLLTTTT!!!! <<< " RENDL;
		std::cerr << _path << ":" << exception.what();
	}

}

void Webserv::run(void) {
	if (_status.test(CONFING)) {
		std::cout << ENDL
			<< "*------------------*" ENDL
			<< "| Webserb  Running |" ENDL
			<< "*------------------*" ENDL;
		_status.set(RUM);
	} else
		_status.set(FAIL);

}

int	Webserv::close(void) {
	if (_status.test(PATH)) {
		(*_file).close();
		delete _file;
	}
	if (_status.test(INSTANCE))
		delete &instance();

	if (_status.test(RUM)) {
		std::cout << ENDL
			<< "*------------------*" ENDL
			<< "| Clossing Webserb |" ENDL
			<< "*------------------*" ENDL;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

void	Webserv::addBlock(Block::type_e &block) {
	if (block == Block::HTTP) {
		return ;
	} else if (block == Block::SERVER) {
		instance()._http.addServer();
	} else if (block == Block::LOCATION) {
		instance()._http.getServers().back().addLocation();
	} else {
		throw (std::runtime_error("Unexpected erorr on addBlock Func!!")); // TODO: Better Error Msg
	}
}

void	Webserv::dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &args) {
	Http	&http = instance()._http;

	if (block == Block::HTTP) {
		tyrHandler<Http, Http::HandlerPointer>(block, name, args, http);
	} else if (block == Block::SERVER) {
		Server	&server = http.getServers().back();
		tyrHandler<Server, Server::HandlerPointer>(block, name, args, server);
	} else if (block == Block::LOCATION) {
		Location	&location = http.getServers().back().getLocations().back();
		tyrHandler<Location, Location::HandlerPointer>(block, name, args, location);
	} else {
		throw (std::runtime_error("Unexpected erorr on add dispatchHandler Func!!")); // TODO: Better Error Msg
	}
}
