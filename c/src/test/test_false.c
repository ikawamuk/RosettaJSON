/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_false.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:48:05 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:01:04 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "json.h"

static int	test_valid_false_case(char *string);
static int	test_invalid_false_case(char *string);

int	test_false()
{
	test_valid_false_case("false");
	test_valid_false_case("falseX");
	test_invalid_false_case("Xfalse");
	test_invalid_false_case("falsXe");
	test_invalid_false_case("fals");
	return (0);
}

static int	test_valid_false_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(json->type == JSON_False);
	json_delete(json);
	return (0);
}

static int	test_invalid_false_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(!json || json->type != JSON_False);
	return (0);
}
