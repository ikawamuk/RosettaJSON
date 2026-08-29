/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_impl_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:51:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 01:08:15 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_IMPL__H
# define JSON_IMPL__H

# include "json.h"
# include "json_error.h"

typedef struct s_parse_buffer
{
	const unsigned char	*content;
	size_t				length;
	size_t				offset;
	size_t				depth;
}	t_parse_buffer;

#endif
