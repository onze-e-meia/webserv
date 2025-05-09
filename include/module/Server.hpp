




#ifndef		SERVER_HPP
# define	SERVER_HPP

#include <string>
#include <vector>

#include "Core.hpp"
#include "Location.hpp"


class	Server: public	Core {
public:
	typedef void	(Server::*HandlerPointer)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

private:
	Server					*_server;
	std::vector<Location>	_locations;
	std::string				_server_name;
	std::string				_host;
	std::string				_port;
	std::string				_listen;

	// Roger
	// std::string _return_code;
	// std::string _return_uri;

public:
	Server(void);
	// ~Server(void);

	static HandlerPointer	selectHandler(ConstStr &name);

	Block::type_e	getBlockType(void);
	void		setName(const std::string &name);
	std::string	getName(void);

	/* Handlers */
	void	server_name_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	host_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	port_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	listen_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

// Server::Server(void): Core(Name::SERVER) {}

#endif		// SERVER_HPP
