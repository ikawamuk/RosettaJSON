/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:02:47 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"
#include "json_error.h"
#include "json_impl_.h"


t_json	*json_parse(const char *json_text)
{
	t_json			*item;
	t_parse_buffer	buffer;

	if (!json_text) return (NULL);
	json_error_reset();
	item = json_new_item();
	if (!item)
	{
		json_set_error(0, FAILED_TO_MEMORY_ALLOCATION);
		return (NULL);
	}
	parse_buffer_init(&buffer, json_text);
	if (parse_value(item, buffer) != 0)
	{
		// parse failuere. json_error is set.
		json_delete(item);
		return (NULL);
	}
	return (item);
}

static void	parse_buffer_init(t_parse_buffer *self, const char *json_text)
{
	self->content = json_text;
	self->length = strlen(json_text);
	self->offset = 0;
	self->depth = 0;
}

static t_json	*json_new_item(void)
{
	t_json	*item = malloc(sizeof(t_json));
	if (item)
		memset(item, 0, sizeof(t_json));
	return (item);
}
