




#include <sstream>
#include <iomanip>
#include "Parser.hpp"
#include "ParseLimits.hpp"
#include "color.hpp"


// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
std::string	Parser::Exception::exceptionClass(ConstStr &str) {
	std::ostringstream	oss;
	oss << RED << str << RENDL;
	return (oss.str());
}

std::string	Parser::Exception::pathLinePos(ConstStr &path, std::size_t line, std::size_t pos) {
	std::ostringstream	oss;
	oss << path << ":" << line << ":" << pos << ": ";
	return (oss.str());
}

// =============================================================================
// PUBLIC
// =============================================================================

// --------------------
// CLASS EXCEPTION
// --------------------
/* Contsructor */
Parser::Exception::Exception(void) {}

Parser::Exception::Exception(const Parser &parser, const std::string &errMsg) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser Error:")
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._token.cursorPos())
		<< TAB << errMsg << ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

/* Destructor */
Parser::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Parser::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// ---------------------------------------
//  CLASS EXCEPTION: Parser Size Limits
// ---------------------------------------
/* Contsructor */
Parser::FileSize::FileSize(ConstStr &path, std::size_t line, std::size_t pos) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser File Size Error:")
		<< pathLinePos(path, line, pos)
		<< "File MAX size must be " << MAX_FILE_SIZE << " or less." << ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::LineLength::LineLength(ConstStr &path, std::size_t line, std::size_t pos, char *str) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser Line Lenght Error:")
		<< pathLinePos(path, line, pos)
		<< "Line MAX lenght must be of size " << MAX_LINE_LEN << " or less." << ENDL
		<< TAB " | " << str << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::DirectiveLength::DirectiveLength(ConstStr &path, std::size_t line,
std::size_t pos, ConstStr &directive) {
	std::ostringstream	oss;

	oss << exceptionClass("Directive Length Error:")
		<< pathLinePos(path, line, pos)
		<< "MAX lenght must be of size " << MAX_DIRECTIVE_LEN << " or less." << ENDL
		<< TAB " | on Directive: " << directive << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

// ----------------------------------
//  CLASS EXCEPTION: Parser Tokens
// ----------------------------------
/* Contsructor */
Parser::ExpectedToken::ExpectedToken(const Parser &parser, ConstStr &directive) {
	std::ostringstream	oss;

	oss << exceptionClass("Expected Token Error:")
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Expected token ';' after directive" << directive << ENDL
		<< std::setw(6) << _line << " | " << parser._innerBlock._name << " { " << directive << RED "'?'" RENDL
		<< "       | " ;
	_errMsg = oss.str();
}

// --------------------------------
// CLASS EXCEPTION Block
// --------------------------------
/* Contsructor */
Parser::WrongBlock::WrongBlock(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock) {
	std::ostringstream	oss;
	std::string			errType("Block Error: ");

	if (outerBlock._module & Block::WEBSERV._module) {
		errType += "First block on webserv must be 'http'.";
	} else if (outerBlock == Block::EMPTY) {
		errType += "Http Block Closed.";
	} else if (directive.empty()) {
		errType += "Empty name.";
	} else if (parser._innerBlock._mask & Block::UNKNOWN._module) {
		errType += "Unknown name.";
	} else
		errType += "Wrong context.";

	oss << exceptionClass(errType)
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Block directive '" << directive << "' is out of context on block: " << outerBlock._name << ENDL
		<< "       | " << outerBlock._name << " {" ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " TAB "'" << directive << "' {...}" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Parser::WrongArgs::WrongArgs(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args) {
	std::ostringstream	oss;
	std::string			errType("Number of Arguments Error: ");
	std::string			argsStr;
	std::string			adjective("more");

	if (parser._innerBlock._module & (Block::HTTP._module | Block::SERVER._module)) {
		errType += parser._innerBlock._name + " must have 0 args.";
	} else if (parser._innerBlock._module & Block::LOCATION._module) {
		errType += parser._innerBlock._name + " must have 1 args.";
		adjective = (args.empty())? "less" : "more";
	}

	for (std::size_t i; i < args.size(); ++i)
		argsStr += args.at(i) + " ";

	oss << exceptionClass(errType)
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " TAB << directive << " '" << argsStr << "' {...}" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}
