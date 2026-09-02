/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 13:10:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:04:45 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static size_t	count_num_str_buf_size(t_parse_buf *const buf);

int	parse_number(t_json *item, t_parse_buf *const buf)
{
	double	number;
	char	*number_c_string;
	char	*after_endp;
	size_t	num_str_buf_size;

	num_str_buf_size = count_num_str_buf_size(buf);
	number_c_string = (char *)calloc(sizeof(char), num_str_buf_size);
	if (!number_c_string)
	{
		json_set_error(buf->offset, FAILED_TO_MEMORY_ALLOCATION);
		return (-1);
	}
	memmove(number_c_string, parse_buf_at_offset(buf), num_str_buf_size);
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

static size_t	count_num_str_buf_size(t_parse_buf *const buf)
{
	size_t	size;
	char	c;

	size = 0;
	while (can_access_at_index(buf, size))
	{
		c = parse_buf_at_offset(buf)[size];
		if (isdigit(c) || c == '.' || c == '-'
			|| c == '+' || c == 'E' || c == 'e')
			size++;
		else
			break ;
	}
	return (size + 1);
}
