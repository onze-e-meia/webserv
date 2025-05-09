/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:57:50 by tforster          #+#    #+#             */
/*   Updated: 2025/04/15 13:07:27 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_H
# define TCP_H

# include <arpa/inet.h>
// # include <sys/types.h>
// # include <sys/socket.h>

# include <string.h>
# include <unistd.h>

typedef enum {
	SERVER_OK,
	SERVER_SOCKET_ERROR,
	SERVER_BIND_ERROR,
	SERVER_LISTEN_ERROR,
	SERVER_ACCEPT_ERROR
}	server_status_e;

typedef struct {
	int socket_fd;
	struct sockaddr_in address;
}	tcp_server_t;

void			debug_log(const char *msg);
server_status_e	bind_tcp_port(tcp_server_t *server, int port);
int				accept_client(int server_fd);

#endif // TCP_H
