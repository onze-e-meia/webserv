#ifndef SERVER_HPP
# define SERVER_HPP

#include <bitset>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "Core.hpp"
#include "Location.hpp"


class	Server: public	Core {
	private:
		std::string		_server_name;
		std::string		_host;
		std::string		_port;
		std::string		_listen;

		std::map<std::string, Location> _locations;

		// Roger
		std::string _return_code;
		std::string _return_uri;


	public:
		Server(void): Core(Name::SERVER) {
			std::cout << YLW "SERVER ADDED TO HTTP " << _blockType  << RENDL;
		}

		BlockType	getBlockType(void) { return _blockType; }
		void		setName(const std::string &name) {_server_name = name; }
		std::string	getName(void) { return (_server_name); }
};

// Server::Server(void): Core(Name::SERVER) {}

#endif // SERVER_HPP
