/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:05:16 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/04 16:06:27 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "json.h"

static char	*read_file_to_buffer(int fd);

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
	if (parse_succeed)
		return (0);
	return (1);
}

static char	*read_file_to_buffer(int fd)
{
	struct stat	st;
	char		*buffer;
	ssize_t		read_bytes;

	if (fstat(fd, &st) < 0 || !S_ISREG(st.st_mode))
		return (NULL);
	buffer = malloc(st.st_size + 1);
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, st.st_size);
	if (read_bytes < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[read_bytes] = '\0';
	return (buffer);
}
