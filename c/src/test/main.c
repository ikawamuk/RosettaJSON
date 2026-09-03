/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:05:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/03 10:13:02 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

int	main(int argc, char *argv[])
{
	t_json	*json;
	char	*s;

	if (argc < 2)
	{
		printf("Usage: %s <JSON text>\n", argv[0]);
		return (0);
	}
	s = NULL;
	json = json_parse(argv[1]);
	if (!json)
		printf("Error: %zd: %s\n", json_get_error_position(), \
		json_get_error_message(json_get_error_code()));
	else
	{
		s = json_generate_unformatted(json);
		if (!s)
			return (1);
		printf("%d\n", json->type);
		printf("%s\n", s);
	}
	json_delete(json);
	free(s);
	return (0);
}
