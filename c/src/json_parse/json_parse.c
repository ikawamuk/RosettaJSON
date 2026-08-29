/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 02:03:36 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include "json.h"
#include "json_error.h"
#include "buffer.h"

static t_json	*json_new_item(void);
static int		parse_value(t_json *item, t_buffer *const buf);
bool			parse_true(t_json *item, t_buffer *const buf);
bool			parse_false(t_json *item, t_buffer *const buf);

bool	parse_null(t_json *item, t_buffer *const buf);


t_json	*json_parse(const char *json_text)
{
	t_json		*item;
	t_buffer	buffer;

	if (!json_text)
		return (NULL);
	json_error_reset();
	item = json_new_item();
	if (!item)
	{
		json_set_error(0, FAILED_TO_MEMORY_ALLOCATION);
		return (NULL);
	}
	buffer_init(&buffer, json_text);
	if (parse_value(item, buffer_skip_whitespace(&buffer)) != 0)
	{
		json_delete(item);
		return (NULL);
	}
	return (item);
}

static int	parse_value(t_json *item, t_buffer *const buf)
{
	char	c;

	if (!buf || !buf->content)
		return (-1);
	if (!can_access_at_index(buf, 0))
		return (-1);
	c = buffer_at_offset(buf)[0];
	if (c == 'n')
		return (parse_null(item, buf));
	else if (c == 't')
		retrun (parse_true(item, buf));
	else if (c == 'f')
	// 	retrun (parse_false(item, buf));
	// else if (c == '-' || isdigit(c))
	// 	return (parse_number(item, buf));
	// else if (c == '"')
	// 	return (parse_string(item, buf));
	// else if (c == '[')
	// 	parse_array(item, buf);
	// else if (c == '{')
	// 	return (parse_object(item, buf));
	return (false);
}

static t_json	*json_new_item(void)
{
	t_json	*item;

	item = malloc(sizeof(t_json));
	if (item)
		memset(item, 0, sizeof(t_json));
	return (item);
}
