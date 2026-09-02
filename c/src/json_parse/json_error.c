/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:11:36 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 02:23:54 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_error.h"

static t_json_error	g_error;

void	json_set_error(size_t pos, t_json_error_code code)
{
	g_error.position = pos;
	g_error.code = code;
}

void	json_error_reset(void)
{
	return (json_set_error(-1, NO_ERROR));
}

int	json_get_error_code(void)
{
	return (g_error.code);
}

size_t	json_get_error_position(void)
{
	return (g_error.position);
}

char	*json_get_error_message(int error_code)
{
	if (error_code == NO_ERROR)
		return ("No error occurred");
	if (error_code == FAILED_TO_MEMORY_ALLOCATION)
		return ("Failed to memmory allocation");
	if (error_code == INVALID_TOKEN)
		return ("Invalid token");
	if (error_code == NESTING_IS_TOO_DEEP)
		return ("Nesting is too deep");
	return ("Unknown error occurred");
}
