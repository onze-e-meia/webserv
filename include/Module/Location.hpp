

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Core.hpp"

class Location: public	Core {
public:
	typedef void	(Location::*HandlerPointer)(ConstStr&, ConstVecStr&, std::size_t line, std::size_t pos);

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
	void	setLocationPath(ConstStr &path);

	std::string getPath(void) const { return (_locationPath); }

	/* Handlers */
	static HandlerPointer	selectHandler(ConstStr &name);
	void	some_location_Handler(ConstStr &name, ConstVecStr &args, std::size_t line, std::size_t pos);

};

#endif // LOCATION_HPP
