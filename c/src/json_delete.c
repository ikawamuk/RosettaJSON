/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:21:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 04:11:44 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "json_error.h"

void	json_delete(t_json *item)
{
	t_json	*next;

	if (!item)
		return ;
	while (item)
	{
		next = NULL;
		if (item->type == JSON_String)
			free(item->_.string_data);
		else if (item->type == JSON_Array)
		{
			json_delete(item->_.array_data.element);
			next = item->_.array_data.next;
		}
		else if (item->type == JSON_Object)
		{
			free(item->_.object_data.key);
			json_delete(item->_.object_data.value);
			next = item->_.object_data.next;
		}
		free(item);
		item = next;
	}
	return ;
}
