




#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <string>
# include <exception>

# include "Http.hpp"

class	Http::Exception: public	std::exception {
protected:
	std::string	_errMsg;
	std::string	_lineAndPos;

public:
	explicit	Exception(const std::string &detail, std::size_t line, std::size_t pos);
	~Exception(void) throw();

	virtual const char	*what() const throw();
};

class	Http::EmptyBlock: public	Http::Exception {
public:
	EmptyBlock(std::size_t line, std::size_t pos);
};

class	Http::WrongBlock: public	Http::Exception {
public:
	WrongBlock(const std::string& detail, std::size_t line, std::size_t pos);
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
