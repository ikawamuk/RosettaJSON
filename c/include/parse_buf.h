/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:51:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 02:15:11 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BUF_H
# define PARSE_BUF_H

# include <stddef.h>

typedef struct s_parse_buf
{
	const unsigned char	*content;
	size_t				length;
	size_t				offset;
	size_t				depth;
}	t_parse_buf;

void		parse_buf_init(t_parse_buf *self, const char *text);
t_parse_buf	*parse_buf_skip_whitespace(t_parse_buf *const buf);
bool		can_read_n_bytes(t_parse_buf const *const buf, size_t len);
bool		can_access_at_index(t_parse_buf const *const buf, size_t idx);
char		*parse_buf_at_offset(t_parse_buf const *const buf);
#endif
