




#include <cstdio>
#include "CountingStream.hpp"
#include "Parser.hpp"
#include "ParseLimits.hpp"

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
CountingStream::CountingStream(std::istream &is): _is(is), _pos(0), _line(1), _size(0) {}

/* Member Functions */
int	CountingStream::get(void) {
	int	ch = _is.get();
	++_pos;
	if (_pos > MAX_LINE_LEN )
		throw (Parser::LineLength(_line, _pos));
	if (ch != EOF)
		++_size;
	if (_size > MAX_FILE_SIZE )
		throw (Parser::FileSize(_line, _pos));
	if (ch == '\n') {
		++_line;
		_pos = 0;
	}
	return ch;
}

int	CountingStream::peek(void) const {
	return (_is.peek());
}

std::size_t	CountingStream::cursorPos(void) const {
	 return (_pos);
}

std::size_t	CountingStream::cursorLine(void) const {
	return (_line);
}

std::size_t	CountingStream::getSize(void) const {
	return (_size);
}
