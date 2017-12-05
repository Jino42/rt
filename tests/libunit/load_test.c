/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/26 16:44:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libunit.h"

void	load_test(t_unit_test **tests, char *name, char flag, int (*f)(void))
{
	t_unit_test	*test;
	t_unit_test	*cur;

	if ((test = malloc(sizeof(*test))) == NULL)
		exit(EXIT_FAILURE);
	test->name = name;
	test->flag = flag;
	test->f = f;
	test->next = NULL;
	cur = *tests;
	if (tests == NULL || *tests == NULL)
	{
		*tests = test;
	}
	else
	{
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = test;
	}
}
