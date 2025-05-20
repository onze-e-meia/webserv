




#include <sstream>
#include <iomanip>
#include "Parser.hpp"
#include "Core.hpp"
#include "color.hpp"

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
std::string	Core::Exception::exceptionClass(ConstStr &str) {
	std::ostringstream	oss;
	oss << RED << str << RENDL;
	return (oss.str());
}

std::string	Core::Exception::pathLinePos(ConstStr &path, std::size_t line, std::size_t pos) {
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
/* Contsructor & Destructor */
Core::Exception::Exception(void) {}

Core::Exception::Exception(const Parser &parser, const std::string &errMsg) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;

	oss << exceptionClass("Core Error:")
		<< pathLinePos(token.getPath(), token.cursorLine(), token.cursorPos())
		<< TAB << errMsg << ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Core::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Core::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// ---------------------------------------
//  CLASS EXCEPTION: Core Size Limits
// ---------------------------------------
/* Contsructor */
Core::NunmbersArgs::NunmbersArgs(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;
	std::string			errType("Number of Arguments Error: ");
	std::string			argsStr;
	std::string			adjective("more");

	if (parser.getInnerBlock()._module & (Block::HTTP._module | Block::SERVER._module)) {
		errType += parser.getInnerBlock()._name + " must have 0 args.";
	} else if (parser.getInnerBlock()._module & Block::LOCATION._module) {
		errType += parser.getInnerBlock()._name + " must have 1 args.";
		adjective = (args.empty())? "less" : "more";
	}

	for (std::size_t i; i < args.size(); ++i)
		argsStr += args.at(i) + " ";

	oss << exceptionClass(errType)
		<< pathLinePos(token.getPath(), token.cursorLine(), parser.getWordStartPos())
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << token.cursorLine() << " | " TAB << directive << " '" << argsStr << "' {...}" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Core::InvalidType::InvalidType(const Parser &parser, ConstStr &directive, const Block::Module &outerBlock, ConstVecStr &args) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;
	std::string			errType("Number of Arguments Error: ");
	std::string			argsStr;
	std::string			adjective("more");

	if (parser.getInnerBlock()._module & (Block::HTTP._module | Block::SERVER._module)) {
		errType += parser.getInnerBlock()._name + " must have 0 args.";
	} else if (parser.getInnerBlock()._module & Block::LOCATION._module) {
		errType += parser.getInnerBlock()._name + " must have 1 args.";
		adjective = (args.empty())? "less" : "more";
	}

	for (std::size_t i; i < args.size(); ++i)
		argsStr += args.at(i) + " ";

	oss << exceptionClass(errType)
		<< pathLinePos(token.getPath(), token.cursorLine(), parser.getWordStartPos())
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << token.cursorLine() << " | " TAB << directive << " '" << argsStr << "' {...}" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}
