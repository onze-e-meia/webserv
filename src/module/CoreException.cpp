




#include <sstream>
#include <iomanip>
#include "Parser.hpp"
#include "Core.hpp"
#include "color.hpp"

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
std::string	Core::Exception::exceptionClass(C_Str &str) {
	std::ostringstream	oss;
	oss << RED << str << RENDL;
	return (oss.str());
}

std::string	Core::Exception::pathLinePos(C_Str &path, std::size_t line, std::size_t pos) {
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

// ------------------------------
//  CLASS EXCEPTION: Directive
// ------------------------------
/* Contsructor */
Core::UnknownDirective::UnknownDirective(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;
	std::string			errType("Directive Error: Unknown name.");
	std::string			argsStr;
	std::string			adjective("more");

	if (args.size() >= 1) {
		for (std::size_t i = 0; i < args.size(); ++i)
			argsStr += args.at(i) + " ";
		argsStr[argsStr.size() - 1] = ';';
	} else
		argsStr = ";";

	oss << exceptionClass(errType)
		<< pathLinePos(token.getPath(), token.cursorLine(), parser.getWordStartPos())
		<< TAB "Directive '" << directive << "' is not a valid directive name:" ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << token.cursorLine() << " | " TAB << directive << TAB << argsStr << ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Core::NumberArgs::NumberArgs(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;
	std::string			errType("Directive Error: Number of Arguments.");
	std::string			argsStr;
	std::string			adjective("more");

	if (args.size() > 1) {
		errType += directive + " can't have more then 1 arg.";
	} else if (args.size() == 0) {
		errType += directive + " must have at least 1 arg.";
		adjective ="less";
	}

	if (args.size() >= 1) {
		for (std::size_t i = 0; i < args.size(); ++i)
			argsStr += args.at(i) + " ";
		argsStr[argsStr.size() - 1] = ';';
	} else
		argsStr = ";";

	oss << exceptionClass(errType)
		<< pathLinePos(token.getPath(), token.cursorLine(), parser.getWordStartPos())
		<< TAB "Directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << token.cursorLine() << " | " TAB << directive << TAB << argsStr << ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Core::InvalidType::InvalidType(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args) {
	const Token			token = parser.getToken();
	std::ostringstream	oss;
	std::string			errType("Directive Error: Inavild Argument Type.");
	std::string			argsStr;
	std::string			adjective("more");

	// if (parser.getInnerBlock()._module & (Block::HTTP._module | Block::SERVER._module)) {
	// 	errType += parser.getInnerBlock()._name + " must have 0 args.";
	// } else if (parser.getInnerBlock()._module & Block::LOCATION._module) {
	// 	errType += parser.getInnerBlock()._name + " must have 1 args.";
	// 	adjective = (args.empty())? "less" : "more";
	// }

	for (std::size_t i = 0; i < args.size(); ++i)
		argsStr += args.at(i) + " ";

	oss << exceptionClass(errType)
		<< pathLinePos(token.getPath(), token.cursorLine(), parser.getWordStartPos())
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << token.cursorLine() << " | " TAB << directive << " '" << argsStr << "' {...}" ENDL
		<< "       | " ;
	_errMsg = oss.str();
}
