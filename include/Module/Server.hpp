




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
	std::string				_server_name;
	std::string				_host;
	std::string				_port;
	std::string				_listen;
	std::vector<Location>	_locations;

	// Roger
	// std::string _return_code;
	// std::string _return_uri;

public:
	/* Contsructor */
	Server(void);

	/* Destructor */
	~Server(void);

	/* Getters */
	std::vector<Location>	&getLocations(void);

	/* Setters */
	void					addLocation(void);

	void		setServerName(ConstStr &name);
	std::string	getServerName(void);

	/* Handlers */
	static HandlerPointer	selectHandler(ConstStr &name);
	void	server_name_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	host_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	port_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
	void	listen_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);
};

// Server::Server(void): Core(Name::SERVER) {}

#endif		// SERVER_HPP
