/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 00:00:00 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/07 00:00:00 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "test_util.h"
#include "rosetta_json/json.h"

static bool	array_equals(t_json_array const *a, t_json_array const *b);
static bool	object_equals(t_json_object const *a, t_json_object const *b);

char	*read_file_to_buffer(int fd)
{
	struct stat	st;
	char		*buffer;
	ssize_t		read_bytes;

	if (fstat(fd, &st) < 0 || !S_ISREG(st.st_mode))
		return (NULL);
	buffer = malloc(st.st_size + 1);
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, st.st_size);
	if (read_bytes < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[read_bytes] = '\0';
	return (buffer);
}

bool	json_equals(const t_json *a, const t_json *b)
{
	if (a == b)
		return (true);
	if (!a || !b || a->type != b->type)
		return (false);
	if (a->type == JSON_Number)
		return (a->_.number_data == b->_.number_data);
	if (a->type == JSON_String)
		return (strcmp(a->_.string_data, b->_.string_data) == 0);
	if (a->type == JSON_Array)
		return (array_equals(a->_.array_data, b->_.array_data));
	if (a->type == JSON_Object)
		return (object_equals(a->_.object_data, b->_.object_data));
	return (true);
}

static bool	array_equals(t_json_array const *a, t_json_array const *b)
{
	while (a && b)
	{
		if (!json_equals(a->element, b->element))
			return (false);
		a = a->next;
		b = b->next;
	}
	return (!a && !b);
}

static bool	object_equals(t_json_object const *a, t_json_object const *b)
{
	while (a && b)
	{
		if (!a->key || !b->key || strcmp(a->key, b->key) != 0)
			return (false);
		if (!json_equals(a->value, b->value))
			return (false);
		a = a->next;
		b = b->next;
	}
	return (!a && !b);
}
