/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 02:01:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 09:14:36 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "json.h"

t_json	*json_new_item(void);

t_json_object	*json_object_new_member(void)
{
	t_json_object	*member;

	member = malloc(sizeof(t_json_object));
	if (!member)
		return (NULL);
	memset(member, 0, sizeof(t_json));
	member->value = json_new_item();
	if (!member->value)
	{
		free(member);
		return (NULL);
	}
	return (member);
}

void	json_object_delete(t_json_object *object)
{
	if (!object)
		return ;
	free(object->key);
	json_delete(object->value);
	json_object_delete(object->next);
	free(object);
}
