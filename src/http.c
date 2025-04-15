#include "http.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

http_parse_e parse_http_request(char *buff, http_request *request);

int read_http_request(int socket_fd, http_request *request) {
	char buffer[8192] = {0};
	ssize_t bytes_read = read(socket_fd, buffer, sizeof(buffer) - 1);

	if (bytes_read <= 0) {
		return HTTP_PARSE_INVALED; // Reading failed or connection closed
	}

	buffer[bytes_read] = '\0';

	// return parse_http_request(buffer, request);

	// strtok(char *str, const char *delim);
	// Always 3 componets
	if (sscanf(buffer, "%7s %2047s %15s", request->method, request->path, request->protocol) != 3) {
		return HTTP_PARSE_INVALED; // Failed to parse the request line
	}
	return HTTP_PARSE_OK;
}


http_parse_e parse_http_request(char *buff, http_request *request) {
	char	*ptr = buff;

	// Method
	while (isspace(*ptr))
		++ptr;
	char	*start = ptr;
	ssize_t	size = 0;
	while (ptr && !isspace(*ptr) && size < HTTP_METHOD_MAX_LEN) {
		++ptr;
		++size;
	}
	if (*ptr == '\0' || size == 0 || size >= HTTP_METHOD_MAX_LEN)
		return HTTP_PARSE_INVALED;
	memcpy(request->method, start, size);
	request->method[size] = '\0';

	// Path
	while (isspace(*ptr))
		++ptr;
	start = ptr;
	size = 0;
	while (ptr && !isspace(*ptr) && size < HTTP_PATH_MAX_LEN) {
		++ptr;
		++size;
	}
	if (*ptr == '\0' || size == 0 || size >= HTTP_PATH_MAX_LEN)
		return HTTP_PARSE_INVALED;
	memcpy(request->path, start, size);
	request->path[size] = '\0';

	// Protocol
	while (isspace(*ptr))
		++ptr;
	start = ptr;
	size = 0;
	while (ptr && !isspace(*ptr) && size < HTTP_PROTOCOL_MAX_LEN) {
		++ptr;
		++size;
	}
	if (size == 0 || size > HTTP_PROTOCOL_MAX_LEN)
		return HTTP_PARSE_INVALED;
	memcpy(request->protocol, start, size);
	request->protocol[size] = '\0';

	while (isspace(*ptr))
		++ptr;
	if (*ptr)
		return HTTP_PARSE_INVALED;

	return HTTP_PARSE_OK;
}
