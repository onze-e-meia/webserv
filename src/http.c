/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:56:18 by tforster          #+#    #+#             */
/*   Updated: 2025/04/15 17:29:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../include/http.h"

// http_parse_e parse_http_request_t(char *buff, http_request_t *request);

int	read_http_request_t(int socket_fd, http_request_t *request) {
	// char	buffer[8192] = {0};
	ssize_t	bytes_read = read(socket_fd, request->buffer, sizeof(request->buffer) - 1);

	if (bytes_read <= 0) {
		return HTTP_PARSE_INVALED;	// Reading failed or connection closed
	}

	request->buffer[bytes_read] = '\0';

	// return parse_http_request_t(buffer, request);

	// strtok(char *str, const char *delim);
	// Always 3 componets
	if (sscanf(request->buffer, "%7s %2047s %15s", request->method, request->path, request->protocol) != 3) {
		return HTTP_PARSE_INVALED;	// Failed to parse the request line
	}
	return HTTP_PARSE_OK;
}


http_parse_e	parse_http_headers(const char *raw_request, http_request_t *request) {
	const char	*line_start = strstr(raw_request, "\r\n");
	if (!line_start)
		return HTTP_PARSE_INVALED;

	line_start += 2;	// Skip the request line
	while (line_start && *line_start && *line_start != '\r' && *line_start != '\n') {
		const char	*line_end = strstr(line_start, "\r\n");
		if (!line_end)
			break;

		size_t	line_length = line_end - line_start;
		char	line[1024] = {0};
		strncpy(line, line_start, line_length);

		char	*colon_pos = strchr(line, ':');
		if (colon_pos) {
			*colon_pos = '\0';
			const char	*key = line;
			const char	*value = colon_pos + 1;

			while (*value == ' ')
				value++;	// Skip leading spaces

			request->headers = realloc(request->headers, sizeof(http_header_t) * (request->header_count + 1));
			if (!request->headers) {
				perror("Failed to allocate memory for headers");
				exit(EXIT_FAILURE);
			}
			strncpy(request->headers[request->header_count].key, key, sizeof(request->headers[request->header_count].key) - 1);
			strncpy(request->headers[request->header_count].value, value, sizeof(request->headers[request->header_count].value) - 1);
			request->header_count++;
		}
		line_start = line_end + 2;
	}
	return HTTP_PARSE_OK;
}

void	free_http_headers(http_request_t *request) {
	if (request->headers) {
		free(request->headers);
		request->headers = NULL;
		request->header_count = 0;
	}
}

void	init_http_response(http_response_t *response) {
	response->status_code = 200;	// Default to OK
	strncpy(response->reason_phrase, "OK", sizeof(response->reason_phrase) - 1);
	response->headers = NULL;
	response->header_count = 0;
	response->body = NULL;
	response->body_length = 0;
}

void	add_http_header(http_response_t *response, const char *key, const char *value) {
	response->headers = realloc(response->headers, sizeof(http_header_t) * (response->header_count + 1));
	if (!response->headers) {
		perror("Failed to allocate memory for headers");
		exit(EXIT_FAILURE);
	}
	strncpy(response->headers[response->header_count].key, key, sizeof(response->headers[response->header_count].key) - 1);
	strncpy(response->headers[response->header_count].value, value, sizeof(response->headers[response->header_count].value) - 1);
	response->header_count++;
}

void	set_http_body(http_response_t *response, const char *body) {
	size_t	body_length = strlen(body) + 1;
	response->body = malloc(sizeof(char) * body_length);
	if (!response->body) {
		perror("Failed to allocate memory for body");
		exit(EXIT_FAILURE);
	}
	memcpy(response->body, body, sizeof(char) * body_length);
	response->body_length = body_length;
}

void	free_http_response(http_response_t *response) {
	if (response->headers) {
		free(response->headers);
		response->headers = NULL;
		response->header_count = 0;
	}
}

void	free_http_body(http_response_t *response) {
	if (response->body) {
		free(response->body);
		response->body = NULL;
		response->body_length = 0;
	}
}

char	*construct_http_response(const http_response_t *response, size_t *response_length) {
	size_t	buffer_size = 1024;
	char	*buffer = malloc(buffer_size);
	if (!buffer) {
		perror("Failed to allocate memory for response buffer");
		exit(EXIT_FAILURE);
	}

	size_t	offset = snprintf(buffer, buffer_size,
		"HTTP/1.1 %d %s\r\n", response->status_code, response->reason_phrase);

	for (size_t i = 0; i < response->header_count; i++) {
		// How many characters would this formatted string take, if I were to actually write it?
		size_t	header_length = snprintf(NULL, 0,
			"%s: %s\r\n", response->headers[i].key, response->headers[i].value);

		while (offset + header_length + 1 > buffer_size) {
			buffer_size *= 2;
			buffer = realloc(buffer, buffer_size);
			if (!buffer) {
				perror("Failed to reallocate memory for response buffer");
				exit(EXIT_FAILURE);
			}
		}
		offset += snprintf(buffer + offset, buffer_size - offset,
			"%s: %s\r\n", response->headers[i].key, response->headers[i].value);
	}
	offset += snprintf(buffer + offset, buffer_size - offset, "\r\n");

	if (response->body) {
		while (offset + response->body_length + 1 > buffer_size) {
			buffer_size *= 2;
			buffer = realloc(buffer, buffer_size);
			if (!buffer) {
				perror("Failed to reallocate memory for response buffer");
				exit(EXIT_FAILURE);
			}
		}
		memcpy(buffer + offset, response->body, response->body_length);
		offset += response->body_length;
	}
	*response_length = offset;
	return buffer;
}

void	send_http_response(int client_fd, const http_response_t *response) {
	size_t	response_length = 0;
	char	*response_data = construct_http_response(response, &response_length);
	size_t	total_sent = 0;

	while (total_sent < response_length) {
		ssize_t	bytes_sent = send(client_fd, response_data + total_sent, response_length - total_sent, 0);

		if (bytes_sent <= 0) {
			perror("Failed to send response");
			break;
		}
		total_sent += bytes_sent;
	}
	free(response_data);
}

// http_parse_e parse_http_request_t(char *buff, http_request_t *request) {
// 	char	*ptr = buff;

// 	// Method
// 	while (isspace(*ptr))
// 		++ptr;
// 	char	*start = ptr;
// 	ssize_t	size = 0;
// 	while (ptr && !isspace(*ptr) && size < HTTP_METHOD_MAX_LEN) {
// 		++ptr;
// 		++size;
// 	}
// 	if (*ptr == '\0' || size == 0 || size >= HTTP_METHOD_MAX_LEN)
// 		return HTTP_PARSE_INVALED;
// 	memcpy(request->method, start, size);
// 	request->method[size] = '\0';

// 	// Path
// 	while (isspace(*ptr))
// 		++ptr;
// 	start = ptr;
// 	size = 0;
// 	while (ptr && !isspace(*ptr) && size < HTTP_PATH_MAX_LEN) {
// 		++ptr;
// 		++size;
// 	}
// 	if (*ptr == '\0' || size == 0 || size >= HTTP_PATH_MAX_LEN)
// 		return HTTP_PARSE_INVALED;
// 	memcpy(request->path, start, size);
// 	request->path[size] = '\0';

// 	// Protocol
// 	while (isspace(*ptr))
// 		++ptr;
// 	start = ptr;
// 	size = 0;
// 	while (ptr && !isspace(*ptr) && size < HTTP_PROTOCOL_MAX_LEN) {
// 		++ptr;
// 		++size;
// 	}
// 	if (size == 0 || size > HTTP_PROTOCOL_MAX_LEN)
// 		return HTTP_PARSE_INVALED;
// 	memcpy(request->protocol, start, size);
// 	request->protocol[size] = '\0';

// 	while (isspace(*ptr))
// 		++ptr;
// 	if (*ptr)
// 		return HTTP_PARSE_INVALED;

// 	return HTTP_PARSE_OK;
// }
