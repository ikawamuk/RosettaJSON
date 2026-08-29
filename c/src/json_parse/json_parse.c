/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:27:51 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"
#include "json_error.h"
#include "parse_buffer.h"

static t_json	*json_new_item(void);
static int		parse_value(t_json *item, t_parse_buffer * const buf);

t_json	*json_parse(const char *json_text)
{
	t_json			*item;
	t_parse_buffer	buffer;

	if (!json_text)
		return (NULL);
	json_error_reset();
	item = json_new_item();
	if (!item)
	{
		json_set_error(0, FAILED_TO_MEMORY_ALLOCATION);
		return (NULL);
	}
	parse_buffer_init(&buffer, json_text);
	if (parse_value(item, parse_buffer_skip_whitespace(&buffer)) != 0)
	{
		json_delete(item);
		return (NULL);
	}
	return (item);
}

static int		parse_value(t_json *item, t_parse_buffer * const buf)
{
	if (!buf || !buf->content)
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
