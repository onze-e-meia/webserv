/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:06:23 by tforster          #+#    #+#             */
/*   Updated: 2025/04/16 13:49:25 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/http.h"

void	sanitize_path(const char *requested_path, char *sanitized_path, size_t buffer_size);
void	serve_file(const char *path, http_response_t *response);
