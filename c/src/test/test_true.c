/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_true.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:48:05 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:01:18 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "json.h"

static int	test_valid_true_case(char *string);
static int	test_invalid_true_case(char *string);

int	test_true()
{
	test_valid_true_case("true");
	test_valid_true_case("trueX");
	test_invalid_true_case("Xtrue");
	test_invalid_true_case("truX");
	test_invalid_true_case("tru");
	return (0);
}

static int	test_valid_true_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(json->type == JSON_True);
	json_delete(json);
	return (0);
}

static int	test_invalid_true_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(!json || json->type != JSON_True);
	return (0);
}
