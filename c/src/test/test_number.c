/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:07:13 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:09:00 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <assert.h>
#include "json.h"

static int	test_valid_number_case(char *string, double expected);
static int	test_invalid_number_case(char *string);

int	test_number()
{
	test_valid_number_case("0", 0);
	test_valid_number_case("1", 1);
	test_valid_number_case("-1", -1);

	test_invalid_number_case("Xnumber");
	test_invalid_number_case("falsXe");
	test_invalid_number_case("fals");
	return (0);
}

static int	test_valid_number_case(char *string, double expected)
{
	t_json	*json;
	json = json_parse(string);
	assert(json->type == JSON_Number && );
	json_delete(json);
	return (0);
}

static int	test_invalid_number_case(char *string)
{
	t_json	*json;
	json = json_parse(string);
	assert(!json || json->type != JSON_Number);
	return (0);
}
