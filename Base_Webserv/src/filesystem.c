/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:06:45 by tforster          #+#    #+#             */
/*   Updated: 2025/04/16 15:56:03 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "../include/http.h"
#include "../include/filesystem.h"

void	sanitize_path(const char *requested_path, char *sanitized_path, size_t buffer_size) {
	const char	*web_root = "./www";

	snprintf(sanitized_path, buffer_size, "%s%s", web_root, requested_path);

	// Prevent directory traversal by normalizing the path
	if (strstr(sanitized_path, ".."))
		strncpy(sanitized_path, "./www/404.html", buffer_size - 1); // Serve a 404 page
}

void	serve_file(const char *path, http_response_t *response) {
	FILE	*file = fopen(path, "rb+");

	if (!file) {
		response->status_code = 404;
		strncpy(response->reason_phrase, "Not Found", sizeof(response->reason_phrase) - 1);
		// file = fopen("./www/404.html", "rb");
		// add_http_header(response, "Contet-Type", "text/html");
		serve_file("./www/404.html", response);
		return ;
	}

	// Determine the file size
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the file content
	char	*file_content = malloc(file_size + 1);
	if (!file_content) {
		perror("Failed to allocate memory for file content");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	fread(file_content, 1, file_size, file);
	fclose(file);
	file_content[file_size] = '\0';

	// Set the response body
	response->body = file_content;
	response->body_length = file_size;

	// Determine content type (basic implementation)
	if (strstr(path, ".html")) {
		add_http_header(response, "Content-Type", "text/html");
	} else if (strstr(path, ".css")) {
		add_http_header(response, "Content-Type", "text/css");
	} else if (strstr(path, ".js")) {
		add_http_header(response, "Content-Type", "application/javascript");
	} else if (strstr(path, ".png")) {
		add_http_header(response, "Content-Type", "image/png");
	} else {
		add_http_header(response, "Content-Type", "application/octet-stream");
	}

	// Add content length header
	char	content_length[32];
	snprintf(content_length, sizeof(content_length), "%zu", file_size);

	add_http_header(response, "Content-Length", content_length);
	// free(file_content);
}
