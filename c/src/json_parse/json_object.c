/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 02:01:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 02:02:29 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

void	json_object_delete(t_json_object *object)
{
	free(object->key);
	json_delete(object->value);
	json_object_delete(object->next);
	free(object);
}
