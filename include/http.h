#ifndef HTTP_H
#define HTTP_H

#define HTTP_MAX_REQUEST_LEN	8192*4
#define HTTP_METHOD_MAX_LEN		8		// Based on maximum method length in HTTP/1.1
#define HTTP_PATH_MAX_LEN		2048	// Practical limit for URIs
#define HTTP_PROTOCOL_MAX_LEN	16		// Standard protocol length (e.g., HTTP/1.1)

typedef enum {
	HTTP_PARSE_OK,
	HTTP_PARSE_INVALED,
}	http_parse_e;

typedef struct {
	char method[HTTP_METHOD_MAX_LEN];
	char path[HTTP_PATH_MAX_LEN];
	char protocol[HTTP_PROTOCOL_MAX_LEN];
}	http_request;

typedef struct {
	char key[256];		// Header key (e.g., "Host")
	char value[512];	// Header value (e.g., "localhost:8080")
}	http_header_t;

int	read_http_request(int socket_fd, http_request *request);

#endif // HTTP_H
