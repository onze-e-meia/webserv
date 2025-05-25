




#ifndef		CORE_EXCEPTION_HPP
# define	CORE_EXCEPTION_HPP

# include <string>
# include <exception>

# include "Core.hpp"

class	Core::Exception: public	std::exception {
protected:
	std::string	_errMsg;
	// std::string	_path;
	// std::size_t	_line;
	// std::size_t	_pos;

	std::string	exceptionClass(C_Str &str);
	std::string	pathLinePos(C_Str &path, std::size_t line, std::size_t pos);

public:
	/* Contsructor & Destructor */
	explicit	Exception(void);
	explicit	Exception(const Parser &parser, const std::string &errMsg);
	virtual		~Exception(void) throw();

	virtual const char	*what(void) const throw();
};

// --------------------------------------
//  CLASS EXCEPTION: Unknown Directive
// --------------------------------------
class	Core::UnknownDirective: public	Core::Exception {
public:
	UnknownDirective(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args);
};

// ----------------------------------------
//  CLASS EXCEPTION: Number of Arguments
// ----------------------------------------
class	Core::NumberArgs: public	Core::Exception {
public:
	NumberArgs(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args);
};

// ---------------------------------
//  CLASS EXCEPTION: Inavild Type
// ---------------------------------
class	Core::InvalidType: public	Core::Exception {
	public:
	InvalidType(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args);
};

#endif		//CORE_EXCEPTION_HPP
