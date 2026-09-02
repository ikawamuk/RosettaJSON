/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:10:40 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:13:15 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

bool	json_is_null(t_json const *const item)
{
	return (item->type == JSON_Null);
}

bool	json_is_true(t_json const *const item)
{
	return (item->type == JSON_True);
}

bool	json_is_false(t_json const *const item)
{
	return (item->type == JSON_False);
}

bool	json_is_number(t_json const *const item)
{
	return (item->type == JSON_Number);
}

bool	json_is_string(t_json const *const item)
{
	return (item->type == JSON_String);
}

bool	json_is_array(t_json const *const item)
{
	return (item->type == JSON_Array);
}

bool	json_is_object(t_json const *const item)
{
	return (item->type == JSON_Object);
}
