/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 13:10:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/07 18:52:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

size_t			count_valid_number_length(t_parse_buf *buf);
static char		*dup_number_string(t_parse_buf *buf, size_t len);

int	parse_number(t_json *item, t_parse_buf *const buf)
{
	double	number;
	char	*number_c_string;
	char	*after_endp;
	size_t	num_str_buf_size;

	num_str_buf_size = count_valid_number_length(buf);
	if (num_str_buf_size == (size_t)-1)
		return (-1);
	number_c_string = dup_number_string(buf, num_str_buf_size);
	if (!number_c_string)
		return (-1);
	number = strtod(number_c_string, &after_endp);
	if (number_c_string == after_endp)
	{
		free(number_c_string);
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	item->type = JSON_Number;
	item->_.number_data = number;
	buf->offset += after_endp - number_c_string;
	free(number_c_string);
	return (0);
}

static char	*dup_number_string(t_parse_buf *buf, size_t len)
{
	char	*number_c_string;

	number_c_string = (char *)calloc(sizeof(char), len + 1);
	if (!number_c_string)
	{
		json_set_error(buf->offset, FAILED_TO_MEMORY_ALLOCATION);
		return (NULL);
	}
	memmove(number_c_string, parse_buf_at_offset(buf), len);
	return (number_c_string);
}
