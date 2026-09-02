/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 01:54:25 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 08:28:05 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

t_json_array	*json_array_new_element(void)
{
	t_json_array	*element;

	element = malloc(sizeof(t_json_array));
	if (!element)
		return (NULL);
	memset(element, 0, sizeof(t_json));
	return (element);
}

void	json_array_delete(t_json_array *array)
{
	json_delete(array->element);
	json_array_delete(array->next);
	free(array);
}
