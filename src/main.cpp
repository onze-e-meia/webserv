




#include "Webserv.hpp"

int main(int argc, char **argv) {
	Webserv::checkPath(argc, argv);
	Webserv::buildConfig();
	Webserv::run();
	return (Webserv::close());
}
