/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 22:17:12 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 02:19:07 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "json_error.h"
#include "parse_buf.h"

static int		unclosed_brackets(t_parse_buf *buf);
static int		success(t_json *item, t_parse_buf *buf, t_json_array *head);
t_json_array	*json_array_new_element(void);
void			json_array_delete(t_json_array *array);
t_json			*json_new_item(void);

int	parse_array(t_json *item, t_parse_buf *const buf)
{
	t_json_array	*tmp_array;

	if (buf->depth >= JSON_NESTING_LIMIT)
		return (-1);
	++buf->depth;
	if (parse_buf_at_offset(buf)[0] != '[')
	{
		json_set_error(buf->offset, INVALID_TOKEN);
		return (-1);
	}
	++buf->offset;
	parse_buf_skip_whitespace(buf);
	if (can_access_at_index(buf, 0) && parse_buf_at_offset(buf)[0] == ']')
		return (success(item, buf, NULL));
	if (!can_access_at_index(buf, 0))
	{
		--buf->offset;
		return (fail(buf, NULL, INVALID_TOKEN));
	}
	if (parse_array_core(&tmp_array, buf) != 0)
		return (-1);
	if (!can_access_at_index(buf, 0) || parse_buf_at_offset(buf)[0] != ']')
		return (fail(buf, tmp_array, INVALID_TOKEN));
	return (success(item, buf, tmp_array));
}

static int	parse_array_core(t_json_array **list, t_parse_buf *const buf)
{
	t_json_array	*cur;
	t_json_array	*next;

	*list = NULL;
	cur = *list;
	while (1)
	{
		next = json_array_new_element();
		if (!next)
			return (fail(buf, *list, FAILED_TO_MEMORY_ALLOCATION));
		if (!*list)
			*list = next;
		else
		{
			cur->next = next;
			next->prev = cur;
			cur = next;
		}
		if (parse_value(cur->element, parse_buf_skip_whitespace(buf)) != 0)
			return (fail(buf, *list, json_get_error_code()));
		parse_buf_skip_whitespace(buf);
		if (!can_access_at_index(buf, 0) || parse_buf_at_offset(buf)[0] != ',')
			break ;
	}
	return (0);
}

static int	fail(t_parse_buf *buf, t_json_array *array, t_json_error_code code)
{
	json_array_delete(array);
	json_set_error(buf->offset, code);
	return (-1);
}

static int	success(t_json *item, t_parse_buf *buf, t_json_array *head)
{
	--buf->depth;
	item->type == JSON_Array;
	item->_.array_data = head;
	++buf->offset;
	return (0);
}
