




#ifndef		PARSE_EXCEPTION_HPP
# define	PARSE_EXCEPTION_HPP

# include <string>
# include <exception>

# include "Parser.hpp"

class	Parser::Exception: public	std::exception {
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

// ---------------------------------------
//  CLASS EXCEPTION: Parser Size Limits
// ---------------------------------------
class	Parser::FileSize: public	Parser::Exception {
public:
	FileSize(C_Str &path, std::size_t line, std::size_t pos);
};

class	Parser::LineLength: public	Parser::Exception {
	public:
	LineLength(C_Str &path, std::size_t line, std::size_t pos, char *str);
};

class	Parser::DirectiveLength: public	Parser::Exception {
public:
	DirectiveLength(C_Str &path, std::size_t line, std::size_t pos, C_Str &directive);
};

// ----------------------------------
//  CLASS EXCEPTION: Parser Tokens
// ----------------------------------
class	Parser::ExpectedToken: public Parser::Exception {
public:
	ExpectedToken(const Parser &Parser, C_Str &directive);
};

// ----------------------------------
//  CLASS EXCEPTION: Parser Blocks
// ----------------------------------
class	Parser::WrongBlock: public	Parser::Exception {
public:
	WrongBlock(const Parser &parser, C_Str &directive, const Block::Module &outerBlock);
};

class	Parser::WrongArgs: public	Parser::Exception {
public:
	WrongArgs(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args);
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
