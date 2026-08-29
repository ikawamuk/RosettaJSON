/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:26:05 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 03:23:49 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>
#include "parse_buf.h"

void	parse_buf_init(t_parse_buf *self, const char *text)
{
	self->content = (const unsigned char *)text;
	self->length = strlen(text);
	self->offset = 0;
	self->depth = 0;
}

t_parse_buf	*parse_buf_skip_whitespace(t_parse_buf *const buf)
{
	if (!buf || !buf->content)
		return (NULL);
	if (!can_access_at_index(buf, 0))
		return (buf);
	while (can_access_at_index(buf, 0)
		&& (parse_buf_at_offset(buf)[0] <= 32))
		buf->offset++;
	if (buf->offset == buf->length)
		buf->offset--;
	return (buf);
}

bool	can_read_n_bytes(t_parse_buf const *const buf, size_t len)
{
	if (!buf || !buf->content)
		return (false);
	return (buf->offset + len <= buf->length);
}

bool	can_access_at_index(t_parse_buf const *const buf, size_t index)
{
	if (!buf || !buf->content)
		return (false);
	return (buf->offset + index < buf->length);
}

char	*parse_buf_at_offset(t_parse_buf const *const buf)
{
	return ((char *)(buf->content + buf->offset));
}
