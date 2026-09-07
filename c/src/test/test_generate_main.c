/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_generate_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 00:00:00 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/07 00:00:00 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "json.h"
#include "test_util.h"

static int	check_round_trip(t_json *original, char *(*generate_fn)(const t_json *));

int	main(int argc, char *argv[])
{
	int		fd;
	char	*json_text;
	t_json	*original;

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
	original = json_parse(json_text);
	free(json_text);
	if (!original)
		return (1);
	if (check_round_trip(original, json_generate_unformatted) != 0
		|| check_round_trip(original, json_generate) != 0)
	{
		json_delete(original);
		return (1);
	}
	json_delete(original);
	return (0);
}

static int	check_round_trip(t_json *original, char *(*generate_fn)(const t_json *))
{
	char	*generated;
	t_json	*reparsed;
	bool	matched;

	generated = generate_fn(original);
	if (!generated)
		return (-1);
	reparsed = json_parse(generated);
	free(generated);
	if (!reparsed)
		return (-1);
	matched = json_equals(original, reparsed);
	json_delete(reparsed);
	if (!matched)
		return (-1);
	return (0);
}
