/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:05:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 03:46:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "json.h"

int	main(int argc, char *argv[])
{
	t_json	*json;

	if (argc < 2)
		return (1);
	json = json_parse(argv[1]);
	if (!json)
		printf("Error: %zd: %s\n", json_get_error_position(), json_get_error_message(json_get_error_code()));
	else
	{
		printf("%d\n", json->type);
		printf("%s\n", json_generate(json));
	}
	return (0);
}
