
#include <cstdlib>
// #include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
// #include <cstdlib>
// #include <cerrno>
#include <cstring>
// #include <sys/stat.h>
#include "path_check.hpp"
// #include "config_Token.hpp"
#include "config_parser.hpp"
#include "Http.hpp"

#define CONF_BUFFER	4096


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path>\n";
		return EXIT_FAILURE;
	}

	char	*path = argv[1];

	// if (!exists(path)) {
	// 	std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
	// 	return EXIT_FAILURE;
	// }

	if (isDirectory(path)) {
		std::cout << "webserv Error: " << path << ": Is a directory\n";
		if (!isRead(path))
			std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
		return EXIT_FAILURE;
	}

	std::ifstream configFile(path);
	if (!configFile.is_open()) {
		std::cerr << "webserv Error: " << path << ": "<< strerror(errno) << "\n";
		return EXIT_FAILURE;
	}

	// Tokenizer tz(configFile);
	// ConfigParser parser(tz);
	// parser.parse();
	// parse(configFile);
	// Http::instantiate(configFile);
	Http::buildConfig(configFile);
	Http::buildConfig(configFile);

	// std::string line;
	// while (std::getline(file, line)) {
	// 	std::cout << line << '\n';
	// }

	configFile.close();
	return EXIT_SUCCESS;
}


// --- Usage example ---
// int main(int argc, char **argv)
// {
// 	std::ifstream file("nginx.conf");
// 	if (!file)
// 	{
// 		std::cerr << "Cannot open config file\n";
// 		return 1;
// 	}

// 	Tokenizer tz(file);
// 	ConfigParser parser(tz);
// 	parser.parse();

// 	return 0;
// }
