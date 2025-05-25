

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Core.hpp"

class Location: public	Core {
public:
	// typedef void	(Location::*HandlerPointer)(C_Str&, C_VecStr&, std::size_t line, std::size_t pos);
	typedef void	(Location::*HandlerPointer)(C_Parser&, C_Str&, C_Block&, C_VecStr&);
	typedef const HandlerSpec<Location::HandlerPointer>	C_LocationSpec;

private:
	std::string	_locationPath;

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
	/* Contsructor */
	Location(void);

	/* Destructor */
	~Location(void);

	/* Setters */
	void	setLocationPath(C_Str &path);

	std::string getPath(void) const { return (_locationPath); }

	/* Handlers */
	static HandlerPointer	selectHandler(C_Str &name);
	void	location_directive_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args);

};

#endif // LOCATION_HPP
