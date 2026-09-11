/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:05:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/11 14:24:24 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "test_util.h"
#include "rosetta_json/json.h"

int	main(int argc, char *argv[])
{
	int		fd;
	char	*json_text;
	t_json	*json_data;
	bool	parse_succeed;

	if (argc < 2)
	{
		dprintf(2, "Usage: %s <test.json>\n", argv[0]);
		return (2);
	}
	fd = open(argv[1], O_RDONLY);
	json_text = read_file_to_buffer(fd);
	if (fd != STDIN_FILENO)
		close(fd);
	if (!json_text)
	{
		dprintf(2, "Error: Could not open or read file: %s\n", argv[1]);
		return (2);
	}
	json_data = json_parse(json_text);
	parse_succeed = (json_data) != NULL;
	json_delete(json_data);
	free(json_text);
	return (!parse_succeed);
}
