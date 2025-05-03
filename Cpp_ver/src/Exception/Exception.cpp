




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
Http::EmptyBlock::EmptyBlock(std::size_t line, std::size_t pos):
	Exception("", line, pos) {
	_errMsg.clear();
	_errMsg += _lineAndPos;
	_errMsg += RED "Empty Block Error: " RST;
	_errMsg += "Empty Directive name." ENDL;
}

/* CLASS Exception::WrongBlock */
/* Contsructor */
Http::WrongBlock::WrongBlock(const std::string& detail, std::size_t line, std::size_t pos):
	Exception(detail, line, pos) {
	_errMsg.clear();
	_errMsg += _lineAndPos;
	_errMsg += RED "Wrong Block Error: " RST;
	_errMsg += "The first Directive name must be 'http'." ENDL;
}
