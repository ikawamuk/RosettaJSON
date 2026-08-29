/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_generate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:22:02 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 03:17:31 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "json.h"
#include "json_error.h"
#include "output_buf.h"

int	generate_null(t_json const *const item, t_output_buf *const buf);
int	generate_true(t_json const *const item, t_output_buf *const buf);
int	generate_false(t_json const *const item, t_output_buf *const buf);

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
		free(buf.content);
		return (NULL);
	}
	rev = realloc(buf.content, buf.offset + 1);
	if (!rev)
	{
		free(buf.content);
		return (NULL);
	}
	rev[buf.offset] = '\0';
	return (rev);
}

static int	generate_value(t_json const *const item, t_output_buf *const buf)
{
	if (!item || buf)
		return (-1);
	if (item->type == JSON_Null)
		return (generate_null(item, buf));
	else if (item->type == JSON_True)
		return (generate_true(item, buf));
	else if (item->type == JSON_False)
		return (generate_false(item, buf));
	return (-1);
}
