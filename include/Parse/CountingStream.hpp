




#ifndef		COUNTING_STREAM_HPP
# define	COUNTING_STREAM_HPP

# include <istream>

class CountingStream {
private:
	char			*_path;
	std::istream	&_inputStream;
	std::size_t		_pos;
	std::size_t		_line;
	std::size_t		_size;

public:
	/* Contsructor & Destructor */
	CountingStream(char *const path, std::istream &is);
	~CountingStream(void);

	/* Getters */
	std::string	getPath(void) const;
	std::size_t	cursorPos(void) const;
	std::size_t	cursorLine(void) const;

	/* Member Functions */
	int	get(void);
	int	peek(void) const;
};

#endif		// COUNTING_STREAM_HPP
