/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 02:20:56 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 02:35:14 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "output_buf.h"

int		generate_value(t_json const *const item, t_output_buf *const buf);
void	update_offset(t_output_buf *const self);

int	generate_array(t_json const *const item, t_output_buf *const buf)
{
	char			*write_pos;
	t_json_array	*cur;
	size_t			length;

	if (!item || !buf)
		return (-1);
	if (buf->depth >= JSON_NESTING_LIMIT)
		return (-1);
	++buf->depth;
	write_pos = ensure(buf, 1);
	if (!write_pos)
		return (-1);
	*write_pos = '[';
	++buf->offset;
	cur = item->_.array_data;
	while (cur)
	{
		if (generate_value(item, buf) != 0)
			return (-1);
		update_offset(buf);
		if (cur->next)
		{
			if (buf->is_formatted)
				length = 2;
			else
				length = 1;
			write_pos = ensure(buf, length + 1);
			if (!write_pos)
				return (-1);
			*write_pos++ = ',';
			if (buf->is_formatted)
				*write_pos++ = ' ';
			*write_pos = '\0';
			buf->offset += length;
		}
		cur = cur->next;
	}
	write_pos = ensure(buf, 2);
	if (!write_pos)
		return (-1);
	*write_pos++ = ']';
	*write_pos = '\0';
	--buf->depth;
	return (0);
}
