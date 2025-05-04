




#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <string>
# include <exception>

# include "Http.hpp"

typedef const std::string	ConstStr;

class	Http::Exception: public	std::exception {
protected:
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

class	Http::DirectiveLength: public	Http::Exception {
public:
	DirectiveLength(ConstStr &directive, std::size_t line, std::size_t pos);
};

class	Http::LineLength: public	Http::Exception {
	public:
	LineLength(std::size_t line, std::size_t pos);
};

class	Http::FileSize: public	Http::Exception {
public:
	FileSize(std::size_t line, std::size_t pos);
};

class	Http::EmptyBlock: public	Http::Exception {
public:
	EmptyBlock(std::size_t line, std::size_t pos);
};

class	Http::HttpClosed: public	Http::Exception {
public:
	HttpClosed(std::size_t line, std::size_t pos);
};

class	Http::FirstBlock: public	Http::Exception {
public:
	FirstBlock(std::size_t line, std::size_t pos);
};

class	Http::SameBlock: public	Http::Exception {
public:
	SameBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos);
};

class	Http::WrongBlock: public	Http::Exception {
public:
	WrongBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos);
};



#endif // EXCEPTION_HPP


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
