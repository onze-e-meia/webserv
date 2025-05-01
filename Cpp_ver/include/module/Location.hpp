

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <bitset>
#include <map>
#include <set>
#include <string>

class Location {
private:
	std::string _root;
	std::set<std::string> _index;
	std::bitset<2> _autoindex;
	std::map<std::string, std::string> _error_page;
	std::size_t _client_max_body_size;
	std::set<std::string> _allow_methods; // limit_except 

	// Roger
	std::string _uri;
	std::string _fastcgi;
	std::string _return_code;
	std::string _return_uri;

	// Rafa
	// int				_instances;
	// PathLocation	_pathLocation;
	// Return			_returnIndex;


	public:

};

#endif // LOCATION_HPP
