/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 22:37:22 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/29 23:23:27 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "json_private.h"

static t_json_error	g_error = {
	.json = NULL,
	.code = NO_ERROR,
	.position = 0
};
