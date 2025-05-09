

# include "Logger.hpp"

/* PRIVATE */

std::string	Logger::timestamp() {
	time_t		now = time(0);
	struct tm	*tm_info = localtime(&now);
	char		buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
	return (std::string(buffer));
}

/* PUBLIC */

Logger::Logger(const std::string &filename) {
	_file.open(filename.c_str(), std::ios::app);
	if (!_file.is_open())
		std::cerr << "Failed to open log file: " << filename << std::endl;
}

Logger::~Logger() {
	if (_file.is_open())
		_file.close();
}

void	Logger::log(const std::string &message) {
	if (_file.is_open())
		_file << "[" << timestamp() << "] " << message << std::endl;
}
