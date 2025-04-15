/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:58:04 by tforster          #+#    #+#             */
/*   Updated: 2025/04/15 17:20:43 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_H
# define HTTP_H

# include <stddef.h>

# define HTTP_MAX_REQUEST_LEN	8192*4	// Apache
# define HTTP_METHOD_MAX_LEN	8		// Based on maximum method length in HTTP/1.1
# define HTTP_PATH_MAX_LEN		2048	// Practical limit for URIs
# define HTTP_PROTOCOL_MAX_LEN	16		// Standard protocol length (e.g., HTTP/1.1)

typedef enum {
	HTTP_PARSE_OK,
	HTTP_PARSE_INVALED,
}	http_parse_e;

typedef struct {
	char key[256];		// Header key (e.g., "Host")
	char value[512];	// Header value (e.g., "localhost:8080")
}	http_header_t;

typedef struct {
	char			buffer[HTTP_MAX_REQUEST_LEN];
	char			method[HTTP_METHOD_MAX_LEN];
	char			path[HTTP_PATH_MAX_LEN];
	char			protocol[HTTP_PROTOCOL_MAX_LEN];
	http_header_t	*headers;
	size_t			header_count;
}	http_request_t;

typedef struct {
	int				status_code;		// Numeric status code (e.g., 200, 404)
	char			reason_phrase[64];	// Text explanation of the status (e.g., "OK", "Not Found")
	http_header_t	*headers;			// Array of HTTP headers (key-value pairs)
	size_t			header_count;		// Number of headers
	char			*body;				// Response body content
	size_t			body_length;		// Length of the response body
}	http_response_t;

int				read_http_request_t(int socket_fd, http_request_t *request);
http_parse_e	parse_http_headers(const char *raw_request, http_request_t *request);
void			free_http_headers(http_request_t *request);

void			init_http_response(http_response_t *response);
void			add_http_header(http_response_t *response, const char *key, const char *value);
void			set_http_body(http_response_t *response, const char *body);
void			free_http_response(http_response_t *response);
void			free_http_body(http_response_t *response);
char			*construct_http_response(const http_response_t *response, size_t *response_length);
void			send_http_response(int client_fd, const http_response_t *response);

#endif // HTTP_H
