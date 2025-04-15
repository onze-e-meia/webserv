/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:57:53 by tforster          #+#    #+#             */
/*   Updated: 2025/04/15 17:35:16 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <stdio.h>
#include "../include/tcp.h"
#include "../include/http.h"
#include "../lib/color.h"

static void	handle_client(int client_fd);
// static void	test_parse(void);

int main() {
	// test_parse();
	// return 0;

	tcp_server_t server = {0};
	server_status_e status = bind_tcp_port(&server, 8080);
	if (status != SERVER_OK) 	{
		debug_log("Server initialization failed");
		exit(EXIT_FAILURE);
	}

	// while (1) {
		int client_fd = accept_client(server.socket_fd);
		if (client_fd == -1) {
			debug_log("Failed to accept client connection");
			close(server.socket_fd);
			exit(EXIT_FAILURE);
		}

		debug_log("Client connected");

		// close(client_fd);
		handle_client(client_fd);
		close(client_fd);
		debug_log("Response sent and client connection closed");
	// }
	close(server.socket_fd);
	return EXIT_SUCCESS;
}

// static void	test_parse(void) {
// 	const char *raw_request =
// 		"GET /index.html HTTP/1.1\r\n"
// 		"Host: localhost:8080\r\n"
// 		"User-Agent: curl/7.68.0\r\n"
// 		"Accept: */*\r\n"
// 		"\r\n";

// 	http_request_t request = {0};
// 	parse_http_headers(raw_request, &request);

// 	printf("\nParsed HTTP Headers:\n");
// 	for (size_t i = 0; i < request.header_count; i++) {
// 		printf("%s: %s\n", request.headers[i].key, request.headers[i].value);
// 	}

// 	free_http_headers(&request);
// }

 void	handle_client(int client_fd) {
	http_request_t	req = {0};

	if (read_http_request_t(client_fd, &req) != HTTP_PARSE_OK) {
		debug_log("Failed to read or parse HTTP request");
		close(client_fd);
		return;
	}

	if (parse_http_headers(req.buffer, &req) != HTTP_PARSE_OK) {
		debug_log("Failed to read or parse HTTP request");
		close(client_fd);
		return;
	}

	debug_log("\nHTTP request parsed successfully");
	printf("Method: %s\n", req.method);
	printf("Path: %s\n", req.path);
	printf("Protocol: %s\n", req.protocol);

	printf(BOLD "\nParsed HTTP Headers:\n" RST);
	for (size_t i = 0; i < req.header_count; ++i)
		printf("%s %s\n", req.headers[i].key, req.headers[i].value);

	http_response_t	response;
	init_http_response(&response);
	add_http_header(&response, "Content-Type", "text/html");
	add_http_header(&response, "Connection", "close");
	set_http_body(&response, "<html><body><h1>Hello, world!</h1></body></html>");

	printf(BOLD "\nInitialized HTTP Response:\n" RST);
	printf("Status Code: %d\n", response.status_code);
	printf("Reason Phrase: %s\n", response.reason_phrase);

	printf(BOLD "\nHTTP Response Headers:\n" RST);
	for (size_t i = 0; i < response.header_count; i++)
		printf("%s: %s\n", response.headers[i].key, response.headers[i].value);
	if (response.body)
		printf("Body: %s\n", response.body);

	printf(BOLD "\nSend HTTP Response:\n" RST);
	send_http_response(client_fd, &response);

	free_http_headers(&req);
	free_http_response(&response);
	free_http_body(&response);
}
