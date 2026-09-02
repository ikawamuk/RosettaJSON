/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:47:36 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:01:11 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "json.h"

static int	test_valid_null_case(char *string);
static int	test_invalid_null_case(char *string);

int	test_null()
{
	test_valid_null_case("null");
	test_valid_null_case("nullX");
	test_invalid_null_case("Xnull");
	test_invalid_null_case("nuXll");
	test_invalid_null_case("nul");
	return (0);
}

static int	test_valid_null_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(json->type == JSON_Null);
	json_delete(json);
	return (0);
}

static int	test_invalid_null_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(!json || json->type != JSON_Null);
	return (0);
}
