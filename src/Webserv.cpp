




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
char			*Webserv::_path(0);
std::ifstream	*Webserv::_file(0);

/* Contsructor */
Webserv::Webserv(void): _http(Http()) {}

/* Member Functions */
Webserv	&Webserv::instance(void) {
	static Webserv *webserv = 0;

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

/* Getters */
char	*Webserv::getPath(void) {
	return (_path);
}

std::ifstream	&Webserv::getFile(void) {
	return (*_file);
}

bool	Webserv::checkInstance(void) {
	return (_status.test(INSTANCE));
}

/* Setters */
void	Webserv::addBlock(Block::Module &block, C_VecStr &args) {
	if (block == Block::HTTP) {
		return ;
	} else if (block == Block::SERVER) {
		Http	&http = instance()._http;
		http.addServer();
	} else if (block == Block::LOCATION) {
		Server	&server = instance()._http.getServers().back();
		server.addLocation();
		server.getLocations().back().setLocationPath(args.at(0));
		std::cout << "	Lacation PATH: " << server.getLocations().back().getPath() << "\n";
	} else {
		throw (std::runtime_error("Unexpected erorr on addBlock Func!!")); // TODO: Better Error Msg
	}
}

/* Member Functions */
void	Webserv::checkPath(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path>\n";
		_status.set(FAIL);
		return ;
	}

	if (isDirectory(argv[1])) {
		std::cerr << "webserv Error: " << argv[1] << ": Is a directory\n";
		if (!isRead(argv[1])) {
			std::cerr << "webserv Error: " << argv[1] << ": "<< strerror(errno) << ENDL;
			_status.set(FAIL);
			return ;
		}
	}
	_path = argv[1];

	std::ifstream *configFile = new std::ifstream(_path);
	if (!(*configFile).is_open()) {
		std::cerr << "webserv Error: " << _path << ": "<< strerror(errno) << ENDL;
		_status.set(FAIL);
		delete configFile;
		return ;
	}
	_file = configFile;
	_status.set(PATH);
}

void	Webserv::buildConfig(void) {
	if (_status.test(PATH) == false) {
		std::cerr << "webserv Error: " << _path << ": Invalid PATH" ENDL;
		_status.set(FAIL);
		return ;
	}

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		Parser().parseConfigFile();
		_status.set(CONFING);
		// Logger	log("some_name.txt");
		// {
		// 	Http	http = instance()._http;
		// 	std::cout
		// 		<< "PATH: " << _path << ENDL
		// 		<< "First  Server Name: " << http.getServers()[0].getServerName() << ENDL
		// 		<< "Second Server Name: " << http.getServers()[1].getServerName() << ENDL
		// 		<< "   Location 1 Root: " << http.getServers()[0].getLocations()[0].getRoot() << ENDL
		// 		<< "   Location 2 Root: " << http.getServers()[0].getLocations()[1].getRoot() << ENDL
		// 		<< "   Location 3 Root: " << http.getServers()[0].getLocations()[2].getRoot() << ENDL;
		// }
	} catch (const std::exception &exception) {
		_status.set(FAIL);
		std::cerr << exception.what();
	}
}

void Webserv::run(void) {
	if (_status.test(CONFING)) {
		std::cout << ENDL
			<< "*------------------*" ENDL
			<< "| Webserv  Running |" ENDL
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
			<< "| Clossing Webserv |" ENDL
			<< "*------------------*" ENDL;
		return EXIT_SUCCESS;
	}
	std::cout << ENDL
		<< "*------------------*" ENDL
		<< "| Webserv  Failure |" ENDL
		<< "*------------------*" ENDL;
	return EXIT_FAILURE;
}

void	Webserv::dispatchHandler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	Http		&http = instance()._http;

	if (outerBlock == Block::HTTP) {
		(http.*handler<Http>(parser, directive, outerBlock, args))(parser, directive, outerBlock, args);
	} else if (outerBlock == Block::SERVER) {
		Server	&server = http.getServers().back();
		(server.*handler<Server>(parser, directive, outerBlock, args))(parser, directive, outerBlock, args);
	} else if (outerBlock == Block::LOCATION) {
		Location	&location = http.getServers().back().getLocations().back();
		(location.*handler<Location>(parser, directive, outerBlock, args))(parser, directive, outerBlock, args);
	} else if (outerBlock == Block::WEBSERV) { // TODO: Change name WEBSERV to CONFIG_FILE
		std::string errName(directive + " ;");
		throw (Parser::WrongBlock(parser, errName, outerBlock));
	} else {
		throw (std::runtime_error("Unexpected error on dispatchHandler Func!!")); // TODO: Better Error Msg
	}
}
