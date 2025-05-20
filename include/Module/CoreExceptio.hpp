




#ifndef		CORE_EXCEPTION_HPP
# define	CORE_EXCEPTION_HPP

# include <string>
# include <exception>

# include "Core.hpp"

class	Parser;

class	Core::Exception: public	std::exception {
protected:
	std::string	_errMsg;
	// std::string	_path;
	// std::size_t	_line;
	// std::size_t	_pos;

	std::string	exceptionClass(ConstStr &str);
	std::string	pathLinePos(ConstStr &path, std::size_t line, std::size_t pos);

public:
	/* Contsructor & Destructor */
	explicit	Exception(void);
	explicit	Exception(const Parser &parser, const std::string &errMsg);
	virtual		~Exception(void) throw();

	virtual const char	*what(void) const throw();
};

// ---------------------------------------
//  CLASS EXCEPTION: Number of Arguments
// ---------------------------------------
class	Core::NunmbersArgs: public	Core::Exception {
public:
	NunmbersArgs(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args);
};

// ---------------------------------------
//  CLASS EXCEPTION: Inavild Type
// ---------------------------------------
class	Core::InvalidType: public	Core::Exception {
	public:
	InvalidType(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args);
};

#endif		//CORE_EXCEPTION_HPP
