/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:51:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:21:40 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BUFFER_H
# define PARSE_BUFFER_H

# include <stddef.h>

typedef struct s_parse_buffer
{
	const unsigned char	*content;
	size_t				length;
	size_t				offset;
	size_t				depth;
}	t_parse_buffer;

void			parse_buffer_init(t_parse_buffer *self, const char *text);
t_parse_buffer	*parse_buffer_skip_whitespace(t_parse_buffer * const buffer);

#endif
