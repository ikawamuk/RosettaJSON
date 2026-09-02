/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:18:21 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 23:40:47 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"
#include "output_buf.h"

int	generate_string(t_json const *const item, t_output_buf *const buf)
{
	size_t	escaped_char_count;
	char	*output;
	size_t	output_length;

	if (!item || !buf)
		return (-1);
	escaped_char_count = count_escaped_char(item->_.string_data);
	output_length = strlen(item->_.string_data) + escaped_char_count;
	output = ensure(buf, output_length + 3);
	if (!output)
		return (-1);
	if (escaped_char_count == 0)
	{
		output[0] = '\"';
		memcpy(output + 1, item->_.string_data, output_length);
		output[output_length + 1] = '\"';
		output[output_length + 2] = '\0';
		return (0);
	}
	return (copy_escaped(output, item->_.string_data, output_length));
}

static char	match_literal_character_for_escaped_char(char input)
{
	if (input == '\\')
		return ('\\');
	if (input == '\"')
		return ('\"');
	if (input == '\b')
		return ('\b');
	if (input == '\f')
		return ('\f');
	if (input == '\n')
		return ('\n');
	if (input == '\r')
		return ('\r');
	if (input == '\t')
		return ('\t');
	return (-1);
}

/* there are unsupported escaped chars & UTF-16 literal is unsupported */
static int	copy_escaped(char *output, char *input, size_t output_length)
{
	char	*out_ptr;

	output[0] = '\"';
	out_ptr = output + 1;
	while (*input)
	{
		if (!is_escaped_char(*input))
			*out_ptr = *input;
		else
		{
			*out_ptr++ = '\\';
			*out_ptr = match_literal_character_for_escaped_char(*input);
			if (*out_ptr == (char)-1)
				return (-1);
		}
		++out_ptr;
	}
	output[output_length + 1] = '\"';
	output[output_length + 2] = '\0';
	return (0);
}

static size_t	count_escaped_char(char *s)
{
	size_t	count;

	if (!s)
		return (-1);
	count = 0;
	while (*s)
		if (is_escaped_char(*s))
			++count;
	return (count);
}

static bool	is_escaped_char(char c)
{
	return (c <= 31 || c == "\"" || c == "\\");
}
