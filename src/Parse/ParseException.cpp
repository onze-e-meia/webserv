




#include <sstream>
#include <iomanip>
#include "Module.hpp"
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

void	Parser::Exception::makeLinePos(ConstStr &errType) {
	std::ostringstream	oss;
	oss << _line << ":" << _pos << ":" TAB RED << errType << RENDL;
	_errMsg = oss.str();
}

void	Parser::Exception::buildErr(ConstStr &msg) {
	std::ostringstream	oss;
	oss << TAB "| " << msg << "." ENDL TAB "|" ENDL;
	_errMsg += oss.str();
}

void	Parser::Exception::build1ArgErr(ConstStr &msg, ConstStr &arg1) {
	std::ostringstream	oss;
	oss << TAB "| Directive '"<< arg1 << "'"
		<< msg << "." ENDL TAB "|" ENDL;
	_errMsg += oss.str();

}

void	Parser::Exception::build2ArgErr(ConstStr &msg, ConstStr &arg1, ConstStr &arg2) {
	std::ostringstream	oss;
	oss << TAB "| Directive Block '"<< arg1 << "' "
		<< msg << " '" << arg2 << "'." ENDL TAB "|" ENDL;
	_errMsg += oss.str();
}

// =============================================================================
// PUBLIC
// =============================================================================

// --------------------
// CLASS EXCEPTION
// --------------------
/* Contsructor */
	// TODO: Include a ref to the outer class, so it can get the line e pos with less args

Parser::Exception::Exception(std::size_t line, std::size_t pos):
_line(line), _pos(pos) {}

Parser::Exception::Exception(void) {}

Parser::Exception::Exception(const Parser &parser):
_path(parser._token.getPath()), _line(parser._token.cursorLine()), _pos(parser._token.cursorPos()) {}

Parser::Exception::Exception(ConstStr &path, std::size_t line, std::size_t pos):
_path(path), _line(line), _pos(pos) {}

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
Parser::FileSize::FileSize(ConstStr &path, std::size_t line, std::size_t pos):
Exception(path, line, pos) {
	std::ostringstream	oss;
	oss << exceptionClass("Parser File Size Error:")
		<< pathLinePos(_path, _line, _pos)
		<< "File MAX size must be " << MAX_FILE_SIZE << " or less." << ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::LineLength::LineLength(ConstStr &path, std::size_t line, std::size_t pos, char *str):
Exception(path, line, pos) {
	std::ostringstream	oss;
	oss << exceptionClass("Parser Line Lenght Error:")
		<< pathLinePos(_path, _line, _pos)
		<< "Line MAX lenght must be of size " << MAX_LINE_LEN << " or less." << ENDL
		<< TAB " | " << str << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::DirectiveLength::DirectiveLength(ConstStr &path, std::size_t line,
std::size_t pos, ConstStr &directive): Exception(path, line, pos) {
	std::ostringstream	oss;
	oss << exceptionClass("Directive Length Error:")
		<< pathLinePos(_path, _line, _pos)
		<< "MAX lenght must be of size " << MAX_DIRECTIVE_LEN << " or less." << ENDL
		<< TAB " | on Directive: " << directive << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

// ----------------------------------
//  CLASS EXCEPTION: Parser Tokens
// ----------------------------------
/* Contsructor */
Parser::UnexpectedToken::UnexpectedToken(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Unexpected Token Error:");
	build1ArgErr(", unexpected Token" , directive);
}

Parser::ExpectedToken::ExpectedToken(const Parser &parser, ConstStr &directive):
Exception(parser) {
	std::ostringstream	oss;
	oss << exceptionClass("Expected Token Error:")
		<< pathLinePos(_path, _line, _pos)
		<< TAB "Expected token ';' after directive" << directive << ENDL
		<< std::setw(6) << _line << " | " << parser._innerBlock._name << " { " << directive << RED "'?'" RENDL
		<< "       | " ;
	_errMsg = oss.str();
}

// --------------------------------
// CLASS EXCEPTION HttpClosed
// --------------------------------
/* Contsructor */
Parser::HttpClosed::HttpClosed(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Http Context Block Closed Error:");
	buildErr("Closing curly brackets '}' has been set. Any further text is out of the 'http' Block");
}

// --------------------------------
// CLASS EXCEPTION FirstBlock
// --------------------------------
/* Contsructor */
Parser::FirstBlock::FirstBlock(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("First Block Error:");
	build1ArgErr(", first Directive Block Name must be 'http'", directive);
}

// --------------------------------
// CLASS EXCEPTION Block
// --------------------------------
/* Contsructor */
Parser::WrongBlock::WrongBlock(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock) {
	std::string	errType("Block Error: ");

	if (directive.empty()) {
		errType += "Empty name.";
	} else if (parser._innerBlock == Block::UNKNOWN) {
		errType += "Unknown name.";
	} else
		errType += "Wrong context.";

	std::ostringstream	oss;
	oss << exceptionClass(errType)
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Block directive '" << directive << "' is out of context on block: " << outerBlock._name << ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " << outerBlock._name << " { '" << directive << "'" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Parser::WrongArgs::WrongArgs(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args) {
	std::string	errType("Number of Arguments Error: ");
	std::string	adjective("more");
	std::string	argsStr;

	if (parser._innerBlock._module & (Block::HTTP._module | Block::SERVER._module)) {
		errType += parser._innerBlock._name + " must have 0 args.";
	} else if (parser._innerBlock._module & Block::LOCATION._module) {
		errType += parser._innerBlock._name + " must have 1 args.";
		adjective = (args.empty())? "less" : "more";
	}

	for (std::size_t i; i < args.size(); ++i)
		argsStr += args.at(i) + " ";

	std::ostringstream	oss;
	oss << exceptionClass(errType)
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " << outerBlock._name
		<< " { " << directive << " '" << argsStr << "'" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}
