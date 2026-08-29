/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 01:18:39 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:26:11 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>
#include "parse_buffer.h"

void	parse_buffer_init(t_parse_buffer *self, const char *text)
{
	self->content = text;
	self->length = strlen(text);
	self->offset = 0;
	self->depth = 0;
}

t_parse_buffer *parse_buffer_skip_whitespace(t_parse_buffer * const buffer)
{
	if (!buffer || !buffer->content)
		return (NULL);
	if (cannot_access_at_index(buffer, 0))
		return (buffer);
	while (can_access_at_index(buffer, 0) && (buffer_at_offset(buffer)[0] <= 32))
		buffer->offset++;
	if (buffer->offset == buffer->length)
		buffer->offset--;
	return (buffer);
}

bool	can_access_at_index(t_parse_buffer const * const buffer, size_t index)
{
	return (buffer && buffer->offset + index < buffer->length);
}

char	*buffer_at_offset(t_parse_buffer const * const buffer)
{
	return (buffer->content + buffer->offset);
}
