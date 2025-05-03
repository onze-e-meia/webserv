


# include <istream>

class CountingStream {
private:
	std::istream	&_is;
	std::size_t		_pos;
	std::size_t		_line;
	std::size_t		_size;

public:
	CountingStream(std::istream &is): _is(is), _pos(0), _line(1), _size(0) {}

	int	get(void) {
		int	ch = _is.get();
		++_pos;
		if (ch != EOF)
			++_size;
		if (ch == '\n') {
			++_line;
			_pos = 0;
		}
		return ch;
	}

	int	peek(void) {
		return (_is.peek());
	}

	std::size_t	getPos(void) const { return (_pos); }
	std::size_t	getLine(void) const { return (_line); }
	std::size_t	getSize(void) const { return (_size); }
};
