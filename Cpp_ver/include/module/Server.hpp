#ifndef SERVER_HPP
# define SERVER_HPP

#include "Location.hpp"
#include <bitset>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

class Server {
	private:
		std::vector<std::string> _host;
		std::vector<std::string> _port;
		std::vector<std::string> _listen;
		std::vector<std::string> _server_name;

		std::string _root;
		std::set<std::string> _index;
		std::bitset<2> _autoindex;
		std::map<std::string, std::string> _error_page;
		std::size_t _client_max_body_size;

		std::map<std::string, Location> _locations;

		// Roger
		std::string _return_code;
		std::string _return_uri;


	public:
};

#endif // SERVER_HPP
