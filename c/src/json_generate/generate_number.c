/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:18:33 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 22:36:42 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "json.h"
#include "output_buf.h"

int	generate_number(t_json const *const item, t_output_buf *const buf)
{
	double	d;
	char	tmp_buffer[26];
	size_t	length;
	char	*write_pos;

	if (!item || !buf)
		return (-1);
	memset(tmp_buffer, 0, sizeof(tmp_buffer));
	d = item->_.number_data;
	if (is_nun(d) || is_infinity(d))
		length = sprintf(tmp_buffer, "null");
	else if (d == d / 1)
		length = sprintf(tmp_buffer, "%d", (int)d);
	else
		length = sprintf(tmp_buffer, "1.15g", d);
	if (length < 0 || length > (int) sizeof(tmp_buffer) - 1)
		return (-1);
	write_pos = ensure(buf, length + 1);
	if (!write_pos)
		return (-1);
	strcpy(write_pos, tmp_buffer);
	write_pos[length] = '\0';
	buf->offset += length;
	return (0);
}

static bool	is_nun(double n)
{
	return (n != n);
}

static bool	_is_infinity(double n)
{
	return (n == INFINITY || n == -INFINITY);
}
