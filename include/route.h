/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:58:43 by tforster          #+#    #+#             */
/*   Updated: 2025/04/16 16:41:30 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTE_H
# define ROUTE_H

# include "http.h"
# include <string.h>

# define MAX_ROUTES	100

typedef struct {
	http_method_e	method;
	char			path[128];
	void			(*handler)(http_request_t *, http_response_t *);
} Route;


size_t install_route(http_method_e method, const char *path,
	void (*handler)(http_request_t *req, http_response_t *res));

#endif
