

#ifndef CONFIG_DIRECTIVES
# define CONFIG_DIRECTIVES

# include <string>
# include <map>

typedef int	directiveSet_e;
#define	INIT_D		0x01
#define CORE_D		0x02
#define HTTP_D		0X04
#define SERVER_D	0x08
#define LOCATION_D	0x16

typedef int	blockType_e;
#define BLOCK_INIT		INIT_D
#define BLOCK_HTTP		(CORE_D | HTTP_D)
#define BLOCK_SERVER	(CORE_D | SERVER_D)
#define BLOCK_LOCATION	(CORE_D | LOCATION_D)

struct Token;

class	Directive;
typedef void	(Directive::*handler_t)(Token&);
typedef	std::map<const std::string, handler_t>		directives_map;
typedef directives_map::const_iterator				directives_it;

class	Directive {
private:
	// static	blocks_map		_blockMap;
	static	directives_map	_direcitveMap[4];
	directives_map	_map;

	std::string XXXX;

	void buildBlockMap();
	void buildDirectiveMap();

public:
	Directive(void): XXXX("") {};
	Directive(blockType_e blcok);
	Directive(Token &token);

	static blockType_e	dispatchBlock(Token &token);
	static handler_t	dispatchDirective(Token &token);

	handler_t			dispatch(Token &token);

	/* HTTP */
	void	http(Token &token);
	void	include(Token &token);
	void	server(Token &token);

	/* SERVER */
	void	host(Token &token);
	void	port(Token &token);
	void	listen(Token &token);
	void	server_name(Token &token);
	void	location(Token &token);

	/* CORE */
	void	root(Token &token);
	void	index(Token &token);
	void	autoindex (Token &toke);
	void	error_page(Token &token);
	void	client_max_body_size(Token &token);
	void	allow_methods(Token &token);
	void	sendfile(Token &token);
	void	keepalive_timeout(Token &token);

}; // namespace Handle

struct	DirectivePair{
	std::string	directiveName;
	handler_t	directiveHandler;
};

// DirectivePair nada;
// nada.directiveName;

namespace	DirectiveSet {
	struct init_s	{
		// DirectivePair	http = {"http",  &Directive::http};
		DirectivePair	include;
		DirectivePair	server;
	};

	const DirectivePair INIT_S[] = {
		{ "http", &Directive::http },
		{ "", NULL },
	};

	const DirectivePair	HTTP_S[] = {
		{ "http", &Directive::http },
		{ "server", &Directive::include },
		{ "location", &Directive::server },
		{ "", NULL },
	};

	const DirectivePair	SERVER_S[] = {
		{ "host", &Directive::host },
		{ "port", &Directive::port },
		{ "listen", &Directive::listen },
		{ "server_name", &Directive::server_name },
		{ "location", &Directive::location },
		{ "", NULL },
	};

	const DirectivePair	CORE_S[] = {
		{ "root", &Directive::root },
		{ "index", &Directive::index },
		{ "autoindex", &Directive::autoindex },
		{ "error_page", &Directive::error_page },
		{ "client_max_body_size", &Directive::client_max_body_size },
		{ "allow_methods", &Directive::allow_methods },
		{ "sendfile", &Directive::sendfile },
		{ "keepalive_timeout", &Directive::keepalive_timeout },
		{ "", NULL },
	};
}



#endif // CONFIG_DIRECTIVES
