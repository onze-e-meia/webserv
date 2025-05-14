




#ifndef		PARSE_EXCEPTION_HPP
# define	PARSE_EXCEPTION_HPP

# include <string>
# include <sstream>
# include <exception>

# include "Parser.hpp"

typedef const std::string				ConstStr;
typedef const std::vector<std::string>	ConstVecStr;
struct	Module;

class	Parser::Exception: public	std::exception {
protected:
	std::string	_errMsg;
	std::string	_path;
	std::size_t	_line;
	std::size_t	_pos;

	std::string	exceptionClass(ConstStr &str);
	std::string	pathLinePos(ConstStr &path, std::size_t line, std::size_t pos);

public:
	/* Contsructor */
	explicit	Exception(void);
	explicit	Exception(const Parser &parser, const std::string &errMsg);

	explicit	Exception(std::size_t line, std::size_t pos);
	~Exception(void) throw();

	virtual const char	*what(void) const throw();
};

// ---------------------------------------
//  CLASS EXCEPTION: Parser Size Limits
// ---------------------------------------
class	Parser::FileSize: public	Parser::Exception {
public:
	FileSize(ConstStr &path, std::size_t line, std::size_t pos);
};

class	Parser::LineLength: public	Parser::Exception {
	public:
	LineLength(ConstStr &path, std::size_t line, std::size_t pos, char *str);
};

class	Parser::DirectiveLength: public	Parser::Exception {
public:
	DirectiveLength(ConstStr &path, std::size_t line, std::size_t pos, ConstStr &directive);
};

// ----------------------------------
//  CLASS EXCEPTION: Parser Tokens
// ----------------------------------
class	Parser::ExpectedToken: public Parser::Exception {
public:
	ExpectedToken(const Parser &Parser, ConstStr &directive);
};

// ----------------------------------
//  CLASS EXCEPTION: Parser Blocks
// ----------------------------------
class	Parser::WrongBlock: public	Parser::Exception {
public:
	WrongBlock(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock);
};

class	Parser::WrongArgs: public	Parser::Exception {
public:
	WrongArgs(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args);
};

#endif		// PARSE_EXCEPTION_HPP


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
