




#include <ostream>
#include "Http.hpp"
#include "color.hpp"

#define DIRECTIVE_LEN 64

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
void	Http::Exception::makeLinePos(ConstStr &errType) {
	std::ostringstream	oss;
	oss << _line << ":" << _pos << ":" TAB RED << errType << RENDL;
	_errMsg = oss.str();
}

void	Http::Exception::buildErr(ConstStr &msg) {
	std::ostringstream	oss;
	oss << TAB << msg << "." ENDL ;
	_errMsg += oss.str();
}

void	Http::Exception::build1ArgErr(ConstStr &msg, ConstStr &arg1) {
	std::ostringstream	oss;
	oss << TAB "| Directive '"<< arg1 << "' "
		<< msg << "." ENDL TAB "|" ENDL;
	_errMsg += oss.str();

}

void	Http::Exception::build2ArgErr(ConstStr &msg, ConstStr &arg1, ConstStr &arg2) {
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
Http::Exception::Exception(std::size_t line, std::size_t pos):
_line(line), _pos(pos) {}

/* Destructor */
Http::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Http::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// ---------------------------------
//  CLASS EXCEPTION DirectiveLength
// ---------------------------------
/* Contsructor */
Http::DirectiveLength::DirectiveLength(ConstStr &directive, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Directive Length Error:");
	std::ostringstream	oss;
	oss << DIRECTIVE_LEN;
	build1ArgErr(", name lenght must be of size " + oss.str() + " or less", directive);
}

// ---------------------------------
//  CLASS EXCEPTION LineLength
// ---------------------------------
/* Contsructor */
Http::LineLength::LineLength(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Empty Block Error:");
	buildErr("Directive '': Empty Directive Block name");
}

// ---------------------------------
//  CLASS EXCEPTION FileSize
// ---------------------------------
/* Contsructor */
Http::FileSize::FileSize(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Empty Block Error:");
	buildErr("Directive '': Empty Directive Block name");
}

// ---------------------------------
//  CLASS EXCEPTION EmptyBlock
// ---------------------------------
/* Contsructor */
Http::EmptyBlock::EmptyBlock(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Empty Block Error:");
	buildErr("Directive '': Empty Directive Block name");
}

// --------------------------------
// CLASS EXCEPTION HttpClosed
// --------------------------------
/* Contsructor */
Http::HttpClosed::HttpClosed(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Http Context Block Closed Error:");
	buildErr("Closing curly brackets '}' has been set. Any further text is out of the 'http' Block");
}

// --------------------------------
// CLASS EXCEPTION FirstBlock
// --------------------------------
/* Contsructor */
Http::FirstBlock::FirstBlock(std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("First Block Error:");
	buildErr("First Directive Block name must be 'http'");
}

// --------------------------------
// CLASS EXCEPTION SameBlock
// --------------------------------
/* Contsructor */
Http::SameBlock::SameBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Same Context Block Error:");
	build2ArgErr("is inside of Directive", directive, contex);

}

// --------------------------------
// CLASS EXCEPTION WrongBlock
// --------------------------------
/* Contsructor */
Http::WrongBlock::WrongBlock(ConstStr &directive, ConstStr &contex, std::size_t line, std::size_t pos):
Exception(line, pos) {
	makeLinePos("Wrong Context Block Error:");
	build2ArgErr("is out of context on Block", directive, contex);
}
