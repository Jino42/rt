/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:44:42 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/25 11:00:31 by apachkof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libunit.h"

int		test_true(void)
{
	return (1);
}

int		test_false(void)
{
	return (0);
}

int		main(void)
{
	t_unit_test		*tests;

	tests = NULL;
	load_test(&tests, "test naze", 0, &test_false);
	load_test(&tests, "test naze", 0, &test_true);
	launch_tests(&tests);
}
