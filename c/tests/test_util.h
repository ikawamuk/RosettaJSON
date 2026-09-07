/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 00:00:00 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/07 00:00:00 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTIL_H
# define TEST_UTIL_H

# include <stdbool.h>
# include "rosetta_json/json.h"

char	*read_file_to_buffer(int fd);
bool	json_equals(const t_json *a, const t_json *b);

#endif
