/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_error.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 00:10:24 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/30 00:11:47 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_ERROR_H
# define JSON_ERROR_H

# include "json.h"

typedef enum e_json_error_code
{
	NO_ERROR
}	t_json_error_code;

typedef struct s_json_error
{
	size_t				position;
	t_json_error_code	code;
}	t_json_error;

void	json_error_reset(void);

#endif
