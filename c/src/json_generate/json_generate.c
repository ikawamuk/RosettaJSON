/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_generate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:22:02 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 09:01:19 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "json_error.h"
#include "output_buf.h"

static char	*generate(t_json const *const item, bool is_formatted);
static int	generate_value(t_json const *const item, t_output_buf *const buf);
static void	update_offset(t_output_buf *const buf);

int			generate_null(t_json const *const item, t_output_buf *const buf);
int			generate_true(t_json const *const item, t_output_buf *const buf);
int			generate_false(t_json const *const item, t_output_buf *const buf);
int			generate_number(t_json const *const item, t_output_buf *const buf);
int			generate_string(t_json const *const item, t_output_buf *const buf);
int			generate_array(t_json const *const item, t_output_buf *const buf);
int			generate_object(t_json const *const item, t_output_buf *const buf);

char	*json_generate(const t_json *item)
{
	return (generate(item, true));
}

char	*json_generate_unformatted(const t_json *item)
{
	return (generate(item, false));
}

static char	*generate(t_json const *const item, bool is_formatted)
{
	char				*rev;
	t_output_buf		buf;

	rev = NULL;
	if (output_buf_init(&buf, is_formatted) != 0)
		return (NULL);
	if (generate_value(item, &buf) != 0)
	{
		free((void *)buf.content);
		return (NULL);
	}
	update_offset(&buf);
	rev = realloc((void *)buf.content, buf.offset + 1);
	if (!rev)
	{
		free((void *)buf.content);
		return (NULL);
	}
	rev[buf.offset] = '\0';
	return (rev);
}

int	generate_value(t_json const *const item, t_output_buf *const buf)
{
	if (!item || !buf)
		return (-1);
	if (item->type == JSON_Null)
		return (generate_null(item, buf));
	if (item->type == JSON_True)
		return (generate_true(item, buf));
	if (item->type == JSON_False)
		return (generate_false(item, buf));
	if (item->type == JSON_Number)
		return (generate_number(item, buf));
	if (item->type == JSON_String)
		return (generate_string(item, buf));
	if (item->type == JSON_Array)
		return (generate_array(item, buf));
	if (item->type == JSON_Object)
		return (generate_object(item, buf));
	return (-1);
}

static void	update_offset(t_output_buf *const buf)
{
	const char	*ptr;

	ptr = NULL;
	if (!buf || !buf->content)
		return ;
	ptr = (const char *)buf->content + buf->offset;
	buf->offset += strlen((const char *)ptr);
}
