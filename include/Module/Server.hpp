




#ifndef		SERVER_HPP
# define	SERVER_HPP

#include <string>
#include <vector>

#include "Core.hpp"
#include "Location.hpp"


class	Server: public	Core {
public:
	// typedef void	(Server::*HandlerPointer)(C_Str&, C_VecStr&, std::size_t line, std::size_t pos);
	typedef void	(Server::*HandlerPointer)(C_Parser&, C_Str&, C_Block&, C_VecStr&);
	typedef const HandlerSpec<Server::HandlerPointer>	C_ServerSpec;

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

	void		setServerName(C_Str &name);
	std::string	getServerName(void);

	/* Handlers */
	static HandlerPointer	selectHandler(C_Str &name);
	void	server_name_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	host_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	port_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
	void	listen_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);
};

// Server::Server(void): Core(Name::SERVER) {}

#endif		// SERVER_HPP
