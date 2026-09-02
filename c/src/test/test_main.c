/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:56:26 by ikawamuk          #+#    #+#             */
/*   Updated: 2026/09/02 20:06:52 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int	test_null();
int	test_true();
int	test_false();

int	main(void)
{
	test_null();
	test_true();
	test_false();
	printf("PASS\n");
	return (0);
}