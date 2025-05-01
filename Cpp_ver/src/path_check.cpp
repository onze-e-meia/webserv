
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include "path_check.hpp"

bool	exists(const char *path) {
	std::cout << access(path, F_OK) << "\n";
	return (access(path, F_OK) == 0);
}

bool	isDirectory(const char *path) {
	struct stat st;
	return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

bool	isRead(const char *path) {
	return (access(path, R_OK) == 0);
}

bool	isWrite(const char *path) {
	return (access(path, W_OK) == 0);
}
