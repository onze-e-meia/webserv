
#ifndef PATH_CHECK_HPP
# define PATH_CHECK_HPP

bool	exists(const char *path);
bool	isDirectory(const char *path);
bool	isRead(const char *path);
bool	isWrite(const char *path);

#endif
