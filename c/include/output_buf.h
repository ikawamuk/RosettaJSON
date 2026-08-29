/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_buf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:25:15 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 02:45:20 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_BUF_H
# define OUTPUT_BUF_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_output_buf
{
	const unsigned char	*content;
	size_t				length;
	size_t				offset;
	size_t				depth;
	bool				is_formatted;
}	t_output_buf;

int	output_buf_init(t_output_buf *self, bool is_formatted);

#endif
