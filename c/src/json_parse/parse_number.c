/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 13:10:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/04 17:46:25 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static bool		is_leading_zero_error(t_parse_buf *buf, char *num_str, size_t idx);
static size_t	count_valid_number_length(t_parse_buf *buf);

int	parse_number(t_json *item, t_parse_buf *const buf)
{
	double	number;
	char	*number_c_string;
	char	*after_endp;
	size_t	num_str_buf_size;

	num_str_buf_size = count_valid_number_length(buf);
	if (num_str_buf_size == (size_t)-1)
		return (-1);
	number_c_string = (char *)calloc(sizeof(char), num_str_buf_size + 1);
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

static bool	is_leading_zero_error(t_parse_buf *buf, char *num_str, size_t idx)
{
	if (num_str[idx] != '0')
		return (false);
	if (can_access_at_index(buf, idx + 1) && isdigit(num_str[idx + 1]))
		return (true);
	return (false);
}

static void	skip_numbers(t_parse_buf *buf, char *num_str, size_t *idx_p)
{
	while (can_access_at_index(buf, *idx_p) && isdigit(num_str[*idx_p]))
		(*idx_p)++;
}

static int	skip_exponent_part(t_parse_buf *buf, char *num_str, size_t *idx_p)
{
	(*idx_p)++;
	if (can_access_at_index(buf, (*idx_p))
		&& (num_str[(*idx_p)] == '+' || num_str[(*idx_p)] == '-'))
		(*idx_p)++;
	if (!can_access_at_index(buf, (*idx_p)) || !isdigit(num_str[(*idx_p)]))
		return (-1);
	skip_numbers(buf, num_str, &(*idx_p));
	return (0);
}

static size_t count_valid_number_length(t_parse_buf *buf)
{
	size_t	idx;
	char	*num_str;

	idx = 0;
	num_str = parse_buf_at_offset(buf);
	if (can_access_at_index(buf, idx) && num_str[idx] == '-')
		idx++;
	if (!can_access_at_index(buf, idx))
		return (-1);
	if (!isdigit(num_str[idx]))
		return (-1);
	if (is_leading_zero_error(buf, num_str, idx))
		return (-1);
	skip_numbers(buf, num_str, &idx);
	if (can_access_at_index(buf, idx) && num_str[idx] == '.')
	{
		idx++;
		if (!can_access_at_index(buf, idx) || !isdigit(num_str[idx]))
			return (-1);
		skip_numbers(buf, num_str, &idx);
	}
	if (can_access_at_index(buf, idx) && (num_str[idx] == 'e' || num_str[idx] == 'E'))
		if (skip_exponent_part(buf, num_str, &idx) != 0)
			return (-1);
	return (idx);
}
