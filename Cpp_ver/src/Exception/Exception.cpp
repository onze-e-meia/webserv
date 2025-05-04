




#include "Http.hpp"

// =============================================================================
// PRIVATE
// =============================================================================

/* CLASS Exception */
/* Contsructor */
Http::Exception::Exception(const std::string &detail, std::size_t line, std::size_t pos) {
	std::ostringstream	oss;
	oss << line << ":" << pos << " In directive '" << detail << "':" ENDL;
	_lineAndPos = oss.str();
	// Add Unknow error or remove detail?
	// _errMsg += _lineAndPos;
}

/* Destructor */
Http::Exception::~Exception(void)  throw() {}

/* Member Functions */
const char	*Http::Exception::what(void) const throw() {
	return (_errMsg.c_str());
}

// =============================================================================
// PUBLIC
// =============================================================================

/* CLASS Exception::EmptyBlock */
/* Contsructor */
Http::EmptyBlock::EmptyBlock(std::size_t line, std::size_t pos): Exception("", line, pos) {
	_errMsg.clear();
	_errMsg = _lineAndPos + RED "Empty Block Error: " RST;
	_errMsg += "Empty Directive Block name." ENDL;
}

/* CLASS Exception::WrongBlock */
/* Contsructor */
Http::FirstBlock::FirstBlock(std::size_t line, std::size_t pos): Exception("http", line, pos) {
	_errMsg.clear();
	_errMsg = _lineAndPos + RED "First Block Error: " RST;
	_errMsg += "The first Directive Block name must be 'http'." ENDL;
}

/* CLASS Exception::WrongBlock */
/* Contsructor */
Http::SameBlock::SameBlock(const std::string &block, const std::string &contex,
	std::size_t line, std::size_t pos): Exception(block, line, pos) {
	_errMsg.clear();
	_errMsg = _lineAndPos + RED "Same Context Block Error: " RST;
	_errMsg += "The Directive Block '" + block + "' is inside of Directive '" + contex + "'." ENDL;
}

/* CLASS Exception::WrongBlock */
/* Contsructor */
Http::WrongBlock::WrongBlock(const std::string &block, const std::string &contex,
	std::size_t line, std::size_t pos): Exception(block, line, pos) {
	_errMsg.clear();
	_errMsg = _lineAndPos + RED "Wrong Context Block Error: " RST;
	_errMsg += "The Directive Block '" + block + "' is out of context on Block '" + contex + "'." ENDL;
}

/* CLASS Exception::HttpClosed */
/* Contsructor */
Http::HttpClosed::HttpClosed(std::size_t line, std::size_t pos): Exception("", line, pos) {
	_errMsg.clear();
	_errMsg = _lineAndPos + RED "Http Context Block Closed Error: " RST;
	_errMsg += "The closing curly braces '}' has been set. Any further text is out of Block." ENDL;
}
