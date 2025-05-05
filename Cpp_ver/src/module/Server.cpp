




#include "module.hpp"
#include "Server.hpp"


Server::Server(void): Core(Block::SERVER) {
	// std::cout << YLW "SERVER ADDED TO HTTP " << _blockType  << RENDL;
}

BlockType	Server::getBlockType(void) { return _blockType; }

void		Server::setName(const std::string &name) {_server_name = name; }

std::string	Server::getName(void) { return (_server_name); }
