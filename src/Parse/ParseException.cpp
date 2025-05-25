




#include <sstream>
#include <iomanip>
#include "Parser.hpp"
#include "color.hpp"

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */
std::string	Parser::Exception::exceptionClass(C_Str &str) {
	std::ostringstream	oss;
	oss << RED << str << RENDL;
	return (oss.str());
}

std::string	Parser::Exception::pathLinePos(C_Str &path, std::size_t line, std::size_t pos) {
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
Parser::Exception::Exception(void) {}

Parser::Exception::Exception(const Parser &parser, const std::string &errMsg) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser Error:")
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._token.cursorPos())
		<< TAB << errMsg << ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Parser::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Parser::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// ---------------------------------------
//  CLASS EXCEPTION: Parser Size Limit
// ---------------------------------------
/* Contsructor */
Parser::FileSize::FileSize(C_Str &path, std::size_t line, std::size_t pos) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser File Size Error:")
		<< pathLinePos(path, line, pos)
		<< "File MAX size must be " << MAX_FILE_SIZE << " or less." << ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::LineLength::LineLength(C_Str &path, std::size_t line, std::size_t pos, char *str) {
	std::ostringstream	oss;

	oss << exceptionClass("Parser Line Lenght Error:")
		<< pathLinePos(path, line, pos)
		<< "Line MAX lenght must be of size " << MAX_LINE_LEN << " or less." << ENDL
		<< TAB " | " << str << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

Parser::DirectiveLength::DirectiveLength(C_Str &path, std::size_t line,
std::size_t pos, C_Str &directive) {
	std::ostringstream	oss;

	oss << exceptionClass("Directive Length Error:")
		<< pathLinePos(path, line, pos)
		<< "MAX lenght must be of size " << MAX_DIRECTIVE_LEN << " or less." << ENDL
		<< TAB " | on Directive: " << directive << " ..." ENDL
		<< TAB " | " ENDL;
	_errMsg = oss.str();
}

// ----------------------------------
//  CLASS EXCEPTION: Token
// ----------------------------------
/* Contsructor */
Parser::ExpectedToken::ExpectedToken(const Parser &parser, C_Str &directive) {
	std::ostringstream	oss;

	oss << exceptionClass("Expected Token Error:")
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Expected token ';' or '{' after directive " << directive << ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " << parser._innerBlock._name << " { " << directive << RED "'?'" RENDL
		<< "       | " ;
	_errMsg = oss.str();
}

// --------------------------------
// CLASS EXCEPTION Block
// --------------------------------
/* Contsructor */
Parser::WrongBlock::WrongBlock(const Parser &parser, C_Str &directive, const Block::Module &outerBlock) {
	std::ostringstream	oss;
	std::string			errType[2] = {"Block Error: ", outerBlock._name + " {"};

	if (outerBlock == Block::WEBSERV) {
		errType[0] += "First block on the config file must be \"http {...\".";
		errType[1] = outerBlock._name;
	} else if (directive.empty()) {
		errType[0] += "Empty block name.";
	} else if (parser._innerBlock == Block::UNKNOWN) {
		errType[0] += "Unknown block name.";
	} else
		errType[0] += "Wrong context.";

	// TODO: Add args?

	oss << exceptionClass(errType[0])
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos)
		<< TAB "Block directive \"" << directive << "\" is out of context on block: " << outerBlock._name << ENDL
		<< "       | " << errType[1] << ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " TAB "'" << directive << "' {..." ENDL
		<< "       | " ;
	_errMsg = oss.str();
}

Parser::WrongArgs::WrongArgs(const Parser &parser, C_Str &directive, const Block::Module &outerBlock, C_VecStr &args) {
	std::ostringstream	oss;
	std::string			errType("Block Number of Arguments Error: ");
	std::string			argsStr;
	std::string			adjective("more");

	if (parser._innerBlock._module & (Block::HTTP._module | Block::SERVER._module)) {
		errType += parser._innerBlock._name + " must have 0 args.";
	} else if (parser._innerBlock._module & Block::LOCATION._module) {
		errType += parser._innerBlock._name + " must have 1 arg.";
		adjective = (args.empty())? "less" : "more";
	}

	if (args.size() >= 1) {
		for (std::size_t i = 0; i < args.size(); ++i)
			argsStr += args.at(i) + " ";
	} else
		argsStr = "       ";

	oss << exceptionClass(errType)
		<< pathLinePos(parser._token.getPath(), parser._token.cursorLine(), parser._wordStartPos + directive.size() + 1)
		<< TAB "Block directive '" << directive << "' have " << adjective << " arguments then it should: " ENDL
		<< "       | " << outerBlock._name << " { " ENDL
		<< std::setw(6) << parser._token.cursorLine() << " | " TAB << directive << " " << argsStr << " {...}" ENDL
		<< "       | " RED << std::setw(6 + directive.size()) << "^"
		<< std::setfill('~') << std::setw(argsStr.size() - 1) << " " << RST;
	_errMsg = oss.str();
}
