




#ifndef		PARSE_EXCEPTION_HPP
# define	PARSE_EXCEPTION_HPP

# include <string>
# include <exception>

# include "Parser.hpp"

typedef const std::string	ConstStr;

class	Parser::Exception: public	std::exception {
protected:
	// TODO: Include a ref to the outer class, so it can get the line e pos with less args
	std::string	_errMsg;
	std::size_t	_line;
	std::size_t	_pos;

	void	makeLinePos(ConstStr &errType);
	void	buildErr(ConstStr &msg);
	void	build1ArgErr(ConstStr &msg, ConstStr &arg1);
	void	build2ArgErr(ConstStr &msg, ConstStr &arg1, ConstStr &arg2);

public:
	explicit	Exception(std::size_t line, std::size_t pos);
	~Exception(void) throw();

	virtual const char	*what(void) const throw();
};

class	Parser::UnexpectedToken: public Parser::Exception {
public:
	UnexpectedToken(ConstStr &directive, std::size_t line, std::size_t pos);
};

class	Parser::ExpectedToken: public Parser::Exception {
public:
	ExpectedToken(ConstStr &directive, std::size_t line, std::size_t pos);
};

class	Parser::DirectiveLength: public	Parser::Exception {
public:
	DirectiveLength(ConstStr &directive, std::size_t line, std::size_t pos);
};

class	Parser::LineLength: public	Parser::Exception {
	public:
	LineLength(std::size_t line, std::size_t pos);
};

class	Parser::FileSize: public	Parser::Exception {
public:
	FileSize(std::size_t line, std::size_t pos);
};

class	Parser::EmptyBlock: public	Parser::Exception {
public:
	EmptyBlock(std::size_t line, std::size_t pos);
};

class	Parser::HttpClosed: public	Parser::Exception {
public:
	HttpClosed(std::size_t line, std::size_t pos);
};

class	Parser::FirstBlock: public	Parser::Exception {
public:
	FirstBlock(ConstStr &directive, std::size_t line, std::size_t pos);
};

class	Parser::SameBlock: public	Parser::Exception {
public:
	SameBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos);
};

class	Parser::WrongBlock: public	Parser::Exception {
public:
	WrongBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos);
};

class	Parser::UnknownDirective: public	Parser::Exception {
public:
	UnknownDirective(ConstStr &directive, std::size_t line, std::size_t pos);
};
#endif		// EXCEPTION_HPP


/* USE CASE ?
class InitError : public Exception {
    int errorCode;
public:
    InitError(const std::string& detail, int code)
        : Exception("InitError: " + detail), errorCode(code) {}

    int code() const { return errorCode; }
};

catch (const MainModule::InitError& e) {
    if (e.code() == 42) {
        std::cerr << "Missing config file\n";
    }
}

catch (const MainModule::Exception& e) {
    if (const MainModule::InitError* init = dynamic_cast<const MainModule::InitError*>(&e)) {
        std::cerr << "Dynamic InitError: " << init->what();
    }
}

*/
