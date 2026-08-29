/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 22:08:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/08/29 22:41:22 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include <stdbool.h>

typedef enum e_json_type
{
	Error,
	Null,
	Boolean,
	Number,
	String,
	Array,
	Object
}	t_json_type;

typedef struct s_json
{
	t_json_type		type;
	union u_json_data
	{
		void	*null_data;
		bool	bool_data;
		int		int_data;
		double	double_data;
		char	*string_data;
		struct s_json_array
		{
			struct s_json	*prev;
			struct s_json	*next;
			struct s_json	*element;
		}	array_data;
		struct s_json_object
		{
			struct s_json	*prev;
			struct s_json	*next;
			char			*key;
			struct s_json	*value;
		}	object_data;
	};
}	t_json;

#endif
