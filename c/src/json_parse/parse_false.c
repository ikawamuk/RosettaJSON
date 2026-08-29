/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_false.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 01:44:28 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 02:01:56 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"
#include "buffer.h"

bool	parse_false(t_json *item, t_buffer *const buf)
{
	if (!can_read_n_bytes(buf, 5)
		|| strncmp((const char *)buffer_at_offset(buf), "false", 5) != 0)
		return (false);
	item->type = JSON_False;
	item->_.bool_data = false;
	buf->offset += 5;
	return (true);
}
