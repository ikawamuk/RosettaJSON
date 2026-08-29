/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:51:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:35:08 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stddef.h>

typedef struct s_buffer
{
	const unsigned char	*content;
	size_t				length;
	size_t				offset;
	size_t				depth;
}	t_buffer;

void		buffer_init(t_buffer *self, const char *text);
t_buffer	*buffer_skip_whitespace(t_buffer *const buffer);
bool		can_read_n_bytes(t_buffer const *const buffer, size_t len);
bool		can_access_at_index(t_buffer const *const buffer, size_t index);
char		*buffer_at_offset(t_buffer const *const buffer);
#endif
