




#include <sstream>
#include "Parser.hpp"
#include "ParseLimits.hpp"
#include "color.hpp"


// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
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
Parser::Exception::Exception(std::size_t line, std::size_t pos): // PUT makeLinePos inside constructor
_line(line), _pos(pos) {}

/* Destructor */
Parser::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Parser::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// ---------------------------------
//  CLASS EXCEPTION UnexpectedToken
// ---------------------------------
/* Contsructor */
Parser::UnexpectedToken::UnexpectedToken(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Unexpected Token Error:");
	build1ArgErr(", unexpected Token" , directive);
}

// ---------------------------------
//  CLASS EXCEPTION ExpectedToken
// ---------------------------------
/* Contsructor */
Parser::ExpectedToken::ExpectedToken(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Expected Token Error:");
	build1ArgErr(", expected ';' or '{' after directive", directive);
}

// ---------------------------------
//  CLASS EXCEPTION DirectiveLength
// ---------------------------------
/* Contsructor */
Parser::DirectiveLength::DirectiveLength(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Directive Length Error:");
	std::ostringstream	oss;
	oss << MAX_DIRECTIVE_LEN;
	build1ArgErr(", Directive Name max lenght must be of size " + oss.str() + " or less", directive);
}

// ---------------------------------
//  CLASS EXCEPTION LineLength
// ---------------------------------
/* Contsructor */
Parser::LineLength::LineLength(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Parse Line Lenght Error:");
	std::ostringstream	oss;
	oss << MAX_LINE_LEN;
	buildErr("Line max lenght must be of size " + oss.str() + " or less");
}

// ---------------------------------
//  CLASS EXCEPTION FileSize
// ---------------------------------
/* Contsructor */
Parser::FileSize::FileSize(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Parse File Size Error:");
	std::ostringstream	oss;
	oss << MAX_FILE_SIZE;
	buildErr("File max size must be " + oss.str() + " or less");
}

// ---------------------------------
//  CLASS EXCEPTION EmptyBlock
// ---------------------------------
/* Contsructor */
Parser::EmptyBlock::EmptyBlock(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Empty Block Error:");
	buildErr("Directive '': Empty Directive Block Name");
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
// CLASS EXCEPTION SameBlock
// --------------------------------
/* Contsructor */
Parser::SameBlock::SameBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Same Context Block Error:");
	build2ArgErr("is inside of the same type Directive", directive, contex);

}

// --------------------------------
// CLASS EXCEPTION WrongBlock
// --------------------------------
/* Contsructor */
Parser::WrongBlock::WrongBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Wrong Context Block Error:");
	build2ArgErr("is out of context on Block", directive, contex);
}

// ---------------------------------
//  CLASS EXCEPTION UnknownDirective
// ---------------------------------
/* Contsructor */
Parser::UnknownDirective::UnknownDirective(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Unknown Block Error:");
	build1ArgErr(", is of Unknown Name" , directive);
}
