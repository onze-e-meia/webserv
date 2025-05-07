

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Core.hpp"

class Location: public	Core {
public:
	typedef void	(Location::*Handler)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

private:
	// Roger
	// std::string _uri;
	// std::string _fastcgi;
	// std::string _return_code;
	// std::string _return_uri;

	// Rafa
	// int			_instances;
	// PathLocation	_pathLocation;
	// Return		_returnIndex;

public:
	Location(void);
	// ~Location(void);

	// static const DirectiveMap	buildMap(void);
	static const Handler		selectHandler(ConstStr &name);

	/* Handlers */
	void	some_location_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);

};

#endif // LOCATION_HPP
