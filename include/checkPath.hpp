
#ifndef		CHECK_PATH_HPP
# define	CHECK_PATH_HPP

bool	exists(const char *path);
bool	isDirectory(const char *path);
bool	isRead(const char *path);
bool	isWrite(const char *path);

#endif		// CHECK_PATH_HPP
