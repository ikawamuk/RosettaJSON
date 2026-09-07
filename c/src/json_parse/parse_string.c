/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 17:54:22 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/04 18:13:11 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static size_t	count_input_string_length(t_parse_buf *const buf);
static int		strliteral_to_string(char *output, char **endp, char *literal);
int				parse_char(char *output, int *read, int *written, char *liter);

int	parse_string(t_json *item, t_parse_buf *const buf)
{
	char	*output;
	char	*buf_endp;
	size_t  max_len;

	max_len = count_input_string_length(buf);
	if (max_len == (size_t)-1)
	{
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	output = calloc(sizeof(char), max_len + 1);
	if (!output)
	{
		json_set_error(buf->offset, FAILED_TO_MEMORY_ALLOCATION);
		return (-1);
	}
	if (strliteral_to_string(output, &buf_endp, parse_buf_at_offset(buf)) != 0)
	{
		free(output);
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	item->type = JSON_String;
	item->_.string_data = output;
	buf->offset = buf_endp - (char *)buf->content;
	return (0);
}

static int	strliteral_to_string(char *output, char **endp, char *literal)
{
	int read_bytes;
    int written_bytes;

	if (!literal || *literal != '"')
		return (-1);
	++literal;
	while (*literal && *literal != '"')
	{
		if (parse_char(output, &read_bytes, &written_bytes, literal) != 0)
			return (-1);
		if (read_bytes <= 0)
            return (-1);
		literal += read_bytes;
		output += written_bytes;
	}
	if (*literal != '"')
        return (-1);
	++literal;
	*output = '\0';
	*endp = literal;
	return (0);
}

static size_t	count_input_string_length(t_parse_buf *const buf)
{
	size_t	i;
	char	*literal_head;

	if (parse_buf_at_offset(buf)[0] != '"')
		return (-1);
	literal_head = parse_buf_at_offset(buf) + 1;
	i = 0;
	while (can_access_at_index(buf, i + 1) && literal_head[i] != '"')
	{
		if (literal_head[i] == '\\')
		{
			++i;
			if (!can_access_at_index(buf, i + 1))
				return (-1);
		}
		++i;
	}
	if (!can_access_at_index(buf, i + 1) || literal_head[i] != '\"')
		return (-1);
	return (i);
} 
