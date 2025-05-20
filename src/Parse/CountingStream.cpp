




#include <cstdio>
#include "CountingStream.hpp"
#include "Parser.hpp"

// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor & Destructor */
CountingStream::CountingStream(char *const path, std::istream &is):
_path(path), _inputStream(is), _pos(0), _line(1), _size(0) {}

CountingStream::~CountingStream(void) {}

/* Getters */
std::string	CountingStream::getPath(void) const {
	return(_path);
}

std::size_t	CountingStream::cursorPos(void) const {
	 return (_pos);
}

std::size_t	CountingStream::cursorLine(void) const {
	return (_line);
}

/* Member Functions */
int	CountingStream::get(void) {
	int	ch = _inputStream.get();
	++_pos;
	if (_pos > MAX_LINE_LEN + 1) {
		char buffer[MAX_LINE_LEN + 1];
		_inputStream.seekg(_size + 1 - _pos).getline(buffer, MAX_LINE_LEN + 1);
		throw (Parser::LineLength(_path, _line, _pos, buffer));
	}
	if (ch != EOF)
		++_size;
	if (_size > MAX_FILE_SIZE )
		throw (Parser::FileSize(_path, _line, _pos));
	if (ch == '\n') {
		++_line;
		_pos = 0;
	}
	return ch;
}

int	CountingStream::peek(void) const {
	return (_inputStream.peek());
}
