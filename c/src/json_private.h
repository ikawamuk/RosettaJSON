/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 22:39:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/29 23:22:31 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PRIVATE_H
# define JSON_PRIVATE_H

# include <stddef.h>
# include "json.h"

typedef enum e_json_error_code
{
	NO_ERROR
}	t_json_error_code;

typedef struct s_json_error
{
	const unsigned char	*json;
	size_t				position;
	t_json_error_code	code;
}	t_json_error;

#endif
