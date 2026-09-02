/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 22:17:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static t_json	*json_new_item(void);
static int		parse_value(t_json *item, t_parse_buf *const buf);
int				parse_true(t_json *item, t_parse_buf *const buf);
int				parse_false(t_json *item, t_parse_buf *const buf);
int				parse_null(t_json *item, t_parse_buf *const buf);
int				parse_number(t_json *item, t_parse_buf *const buf);
int				parse_string(t_json *item, t_parse_buf *const buf);

t_json	*json_parse(const char *json_text)
{
	t_json		*item;
	t_parse_buf	buffer;

	if (!json_text)
		return (NULL);
	json_error_reset();
	item = json_new_item();
	if (!item)
	{
		json_set_error(0, FAILED_TO_MEMORY_ALLOCATION);
		return (NULL);
	}
	parse_buf_init(&buffer, json_text);
	if (parse_value(item, parse_buf_skip_whitespace(&buffer)) != 0)
	{
		json_delete(item);
		return (NULL);
	}
	return (item);
}

static int	parse_value(t_json *item, t_parse_buf *const buf)
{
	char	c;

	if (!buf || !buf->content || !can_access_at_index(buf, 0))
		return (-1);
	c = parse_buf_at_offset(buf)[0];
	if (c == 'n')
		return (parse_null(item, buf));
	else if (c == 't')
		return (parse_true(item, buf));
	else if (c == 'f')
		return (parse_false(item, buf));
	else if (c == '-' || isdigit(c))
		return (parse_number(item, buf));
	else if (c == '"')
		return (parse_string(item, buf));
	else if (c == '[')
		parse_array(item, buf);
	// else if (c == '{')
	// 	return (parse_object(item, buf));
	json_set_error(buf->offset, INVALID_TOKEN);
	return (-1);
}

static t_json	*json_new_item(void)
{
	t_json	*item;

	item = malloc(sizeof(t_json));
	if (item)
		memset(item, 0, sizeof(t_json));
	return (item);
}
