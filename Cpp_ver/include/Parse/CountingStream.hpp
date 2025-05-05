




#ifndef		COUNTING_STREAM_HPP
# define	COUNTING_STREAM_HPP

# include <istream>

class CountingStream {
private:
	std::istream	&_is;
	std::size_t		_pos;
	std::size_t		_line;
	std::size_t		_size;

public:
	CountingStream(std::istream &is);

	int	get(void);
	int	peek(void) const;

	std::size_t	cursorPos(void) const;
	std::size_t	cursorLine(void) const;
	std::size_t	getSize(void) const;
};

#endif		// COUNTING_STREAM_HPP
