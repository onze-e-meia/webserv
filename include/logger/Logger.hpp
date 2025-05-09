

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <fstream>
# include <iostream>
# include <ctime>
# include <sstream>

class Logger {
private:
	std::ofstream	_file;

	std::string	timestamp();

public:
	Logger(const std::string &filename);
	~Logger();

	void	log(const std::string &message);

};

#endif // Logger
