/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:34:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 02:44:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "output_buf.h"

int	output_buf_init(t_output_buf *self, bool is_formatted)
{
	static const size_t	default_buffer_size = 256;

	self->content = malloc(sizeof(char) * default_buffer_size);
	self->length = default_buffer_size;
	self->offset = 0;
	self->length = 0;
	self->is_formatted = is_formatted;
	if (self->content)
		return (-1);
	return (0);
}
