/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:52:04 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/07 18:52:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "json.h"
#include "parse_buf.h"

static bool		is_leading_zero_error(t_parse_buf *buf, char *num_str,
					size_t idx);
static void		skip_numbers(t_parse_buf *buf, char *num_str, size_t *idx_p);
static int		skip_fraction_part(t_parse_buf *buf, char *num_str,
					size_t *idx_p);
static int		skip_exponent_part(t_parse_buf *buf, char *num_str,
					size_t *idx_p);

size_t	count_valid_number_length(t_parse_buf *buf)
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
		if (skip_fraction_part(buf, num_str, &idx) != 0)
			return (-1);
	if (can_access_at_index(buf, idx)
		&& (num_str[idx] == 'e' || num_str[idx] == 'E'))
		if (skip_exponent_part(buf, num_str, &idx) != 0)
			return (-1);
	return (idx);
}

static bool	is_leading_zero_error(t_parse_buf *buf, char *num_str, size_t idx)
{
	if (num_str[idx] != '0')
		return (false);
	if (can_access_at_index(buf, idx + 1) && isdigit(num_str[idx + 1]))
		return (true);
	return (false);
}

static int	skip_fraction_part(t_parse_buf *buf, char *num_str, size_t *idx_p)
{
	(*idx_p)++;
	if (!can_access_at_index(buf, *idx_p) || !isdigit(num_str[*idx_p]))
		return (-1);
	skip_numbers(buf, num_str, idx_p);
	return (0);
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
