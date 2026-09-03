/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:05:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 10:02:24 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

int	main(int argc, char *argv[])
{
	t_json	*json;

	if (argc < 2)
	{
		printf("Usage: %s <JSON text>\n", argv[0]);
		return (0);
	}
	json = json_parse(argv[1]);
	if (!json)
		printf("Error: %zd: %s\n", json_get_error_position(), \
		json_get_error_message(json_get_error_code()));
	else
	{
		char	*s = json_generate(json);
		if (!s)
			return (1);
		printf("%d\n", json->type);
		printf("%s\n", s);
		free(s);
	}
	json_delete(json);
	
	return (0);
}
