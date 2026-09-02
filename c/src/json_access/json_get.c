/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:13:26 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:25:54 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "json.h"

double	json_get_number(t_json const *const number)
{
	return (number->_.number_data);
}

char	*json_get_string(t_json const *const string)
{
	return (string->_.string_data);
}

size_t	json_get_array_size(t_json const *const array)
{
	size_t				size;
	struct s_json_array	*cur;

	cur = &array->_.array_data;
	if (!cur->element)
		return (0);
	size = 0;
	while (cur)
	{
		++size;
		cur = cur->next;
	}
	return (size);
}

t_json	*json_get_array_element(t_json const *const array, size_t index)
{
	size_t				i;
	struct s_json_array	*cur;

	cur = &array->_.array_data;
	i = 0;
	while (cur)
	{
		if (i == index)
			return (cur->element);
		cur = cur->next;
		++i;
	}
	return (NULL);
}

bool	json_has_object_item(t_json const *const object, const char *key)
{
	struct s_json_object	*cur;

	cur = &object->_.object_data;
	while (cur)
	{
		if (cur->key && strcmp(cur->key, key) == 0 && cur->value)
			return (true);
		cur = cur->next;
	}
	return (false);
}

t_json	*json_get_object_item(t_json const *const object, const char *key)
{
	struct s_json_object	*cur;

	cur = &object->_.object_data;
	while (cur)
	{
		if (cur->key && strcmp(cur->key, key) == 0 && cur->value)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

