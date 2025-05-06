




#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Http.hpp"

#include "color.hpp"

#define HTTP_NAME_HANDLER(name) { #name, static_cast<handler_t>(&Http::name##_Handler) }

static const NameHandler	HTTP_HANDLER[] = {
	HTTP_NAME_HANDLER(mime),
	HTTP_NAME_HANDLER(include),
	{ "", NULL },
};

static const DirectiveMap	HTTP_MAP = Http::buildMap();

// =============================================================================
// PRIVATE
// =============================================================================

Http::status	Http::_status(0);

/* Contsructor */
Http::Http(void): Core(Block::HTTP) {}

/* Destructor */
Http::~Http() {}

Http &Http::operator=(const Http &other) {
	if (this != &other) {
		_status = other._status;
	}
	return (*this);
}

/* Member Functions */
const DirectiveMap	Http::buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; HTTP_HANDLER[i]._handler != NULL; ++i)
		map[HTTP_HANDLER[i]._name] = HTTP_HANDLER[i]._handler;
	return (map);
}

const handler_t	Http::selectHandler(ConstStr &name) {
	DirectiveConst_it	it = HTTP_MAP.find(name);
	DirectiveConst_it	end = HTTP_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
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
}

void	Http::addLocation(void) {
	_servers.back();
	std::cout << YLW "LOCATION ADDED TO SERVER" RENDL;
}

// =============================================================================
// PUBLIC
// =============================================================================

/* Member Functions */
void	Http::buildConfig(std::ifstream &file) {
	std::string	path = "src/somefile";

	try {
		if (_status.test(CONFING)) {
			std::ostringstream	oss;
			oss << H_BLU "Config status already build\n" RST;
			throw (std::runtime_error(oss.str()));
		}
		Parser	parse(file);
		parse.parseConfigFile();
		_status.set(CONFING);
		// Logger	log("some_name.txt");
		// _status = EXIT_SUCCESS;
	} catch (const std::exception &exception) {
		_status.set(FAIL);
		std::cerr << RED " >>> HHHHAAAAALLLLTTTT!!!! <<< " RENDL;
		std::cerr << path << ":" << exception.what();
	}
	Http	&http = Http::instance();
	// http._servers[0].setName("Some name! 0 ");
	// http._servers[1].setName("Some name! 1 ");
	// http._servers[2].setName("Some name! 2 ");
	std::cout << "Servers Name: " ENDL
		<< http._servers[0].getName() << ENDL
		<< http._servers[1].getName() << ENDL
		<< http._servers[2].getName() << ENDL;
}

void	Http::addBlock(Block::type_e &block) {
	Http	&http = Http::instance();

	if (block == Block::SERVER) {
		http.addServer();
		// http._servers.push_back(Server());
	}
	if (block == Block::LOCATION) {
		http.addLocation();
	}
}

template <typename F, typename M>
F	callHandler(ConstStr &name) {
	F	method = NULL;
	if (method = Core::selectHandler(name))
		return (method);
	if (method = M::selectHandler(name))
		return (method);
	return (NULL);
}

void	Http::dispatchHandler(Block::type_e block, ConstStr &name, ConstVecStr &vec) {
	Http	&http = Http::instance();
	handler_t	method;

	std::size_t					line = 1;
	std::size_t					pos = 2;

	if (block == Block::HTTP) {
		method = callHandler<handler_t, Http>(name);
		if (method) {
			std::cout << GRN TAB ">>>> On HTTP Found: " TAB << name << RENDL;
			(http.*method)(name, vec, line, pos);
		} else
			std::cout << RED TAB ">>>> UNKNOW DIRETIVE!!!! " TAB << name << RENDL;
	}
	if (block == Block::SERVER) {
		// Server	&server = http._servers.back();
		method = callHandler<handler_t, Server>(name);
		if (method) {
			std::cout << GRN TAB ">>>> On SERVER Found: " TAB << name << vec[0] << RENDL;
			(http._servers.back().*method)(name, vec, line, pos);
			std::cout << GRN TAB ">>>> SERVER NAME: " TAB << http._servers.back().getName() << RENDL;
		} else
			std::cout << RED TAB ">>>> UNKNOW DIRETIVE!!!! " TAB << name << RENDL;
	}

	// const Module::module_e modules[] = {
	// 	Module::CORE, Module::HTTP, Module::SERVER, Module::LOCATION, Module::EMPTY,
	// };

	// for (std::size_t i = 0; modules[i] != Module::EMPTY; ++i) {
	// 	method = Core::handleDirective(name);
	// 	if (method)
	// 		return (method);
	// }
	// return (method);

	// if (name == "server_name")
	// 	http._servers.back().server_name("asdsd", std::vector<std::string>(0), 1, 1);
}

std::string	Http::getRoot() const {
	return (_root);
};

/* Handlers */
void	Http::mime_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {

}

void	Http::include_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos) {
	std::cout << GRN TAB "CALL INCLUDE HANDLER Founs: " TAB << name << line << pos << RENDL;
}
