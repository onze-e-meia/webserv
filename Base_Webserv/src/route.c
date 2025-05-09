/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:03:49 by tforster          #+#    #+#             */
/*   Updated: 2025/04/16 16:05:03 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/route.h"
#include "../include/http.h"

Route routes[MAX_ROUTES];
int route_count = 0;

size_t install_route(http_method_e method, const char *path,
	void (*handler)(http_request_t *req, http_response_t *res)) {

	if (route_count < MAX_ROUTES) {
		routes[route_count].method = method;
		strcpy(routes[route_count].path, path);
		routes[route_count].handler = handler;
		return ++route_count;
	}
	return route_count;
}
