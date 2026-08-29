/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:11:36 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 00:17:24 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_error.h"

static t_json_error	g_error;

void	json_error_reset(void) {
	g_error.code = NO_ERROR;
	g_error.position = (size_t)-1;
}

int		json_get_error_code(void)
{
	return (g_error.code);
}

char	*json_get_error_message(int error_code)
{
	switch (error_code)
	{
		case NO_ERROR:
			return ("No error occurred");
		default:
			return ("Unknown error occurred");
	}
}

size_t	json_get_error_position(void)
{
	return (g_error.position);
}
