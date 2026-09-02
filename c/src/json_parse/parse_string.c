/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 17:54:22 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 23:39:26 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static size_t	count_output_string_length(t_parse_buf *const buf);
static int		strliteral_to_string(char *output, char **endp, char *literal);

int	parse_string(t_json *item, t_parse_buf *const buf)
{
	char	*output;
	char	*buf_endp;
	size_t	output_len;

	output_len = count_output_string_length(buf);
	if (output_len == (size_t)-1)
	{
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	output = calloc(sizeof(char), output_len + 1);
	if (!output)
	{
		json_set_error(buf->offset, FAILED_TO_MEMORY_ALLOCATION);
		return (-1);
	}
	if (strliteral_to_string(output, &buf_endp, parse_buf_at_offset(buf)) != 0)
	{
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	item->type = JSON_String;
	item->_.string_data = output;
	buf->offset = buf_endp - (char *)buf->content;
	return (0);
}

static char	match_escaped_char(char *escaped_str)
{
	if (escaped_str[0] != '\\')
		return (-1);
	if (escaped_str[1] == 'b')
		return ('\b');
	if (escaped_str[1] == 'f')
		return ('\f');
	if (escaped_str[1] == 'n')
		return ('\n');
	if (escaped_str[1] == 'r')
		return ('\r');
	if (escaped_str[1] == 't')
		return ('\t');
	if (escaped_str[1] == '\"'
		|| escaped_str[1] == '\\' || escaped_str[1] == '/')
		return (escaped_str[1]);
	return (-1);
}

/* UTF-16 literal is unsupported */
static int	strliteral_to_string(char *output, char **endp, char *literal)
{
	size_t	i;
	char	c;

	i = 0;
	if (literal[i++] != '\"')
		return (-1);
	while (literal[i] != '\"')
	{
		if (literal[i] != '\\')
			*output++ = literal[i++];
		else
		{
			c = match_escaped_char(literal + i);
			if (c == -1)
				return (-1);
			*output++ = c;
			i += 2;
		}
	}
	*endp = literal + i + 1;
	return (0);
}

static size_t	count_output_string_length(t_parse_buf *const buf)
{
	size_t	i;
	size_t	skipped_bytes;
	char	*literal_head;

	literal_head = parse_buf_at_offset(buf) + 1;
	if (parse_buf_at_offset(buf)[0] != '\"')
		return (-1);
	i = 0;
	skipped_bytes = 0;
	while (can_access_at_index(buf, i) && literal_head[i] != '\"')
	{
		if (literal_head[i] == '\\')
		{
			if (i + 1 >= buf->length)
				return (-1);
			++i;
			++skipped_bytes;
		}
		++i;
	}
	if (!can_access_at_index(buf, i) || literal_head[i] != '\"')
		return (-1);
	return (i - skipped_bytes);
}
