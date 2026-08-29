/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_false.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 01:44:28 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 03:48:54 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

int	parse_false(t_json *item, t_parse_buf *const buf)
{
	if (!can_read_n_bytes(buf, 5)
		|| strncmp((const char *)parse_buf_at_offset(buf), "false", 5) != 0)
	{
		json_set_error(buf->offset, FAILED_TO_MEMORY_ALLOCATION);
		return (-1);
	}
	item->type = JSON_False;
	item->_.bool_data = false;
	buf->offset += 5;
	return (0);
}
