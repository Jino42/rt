/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:16:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/08 18:57:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests_rt.h"

static char *g_test[] = {""};

static int (*g_fun[])(void) = {&tests_gen_launcher,
								&tests_camera_launcher,
								&tests_light_launcher,
								&tests_obj_ccp_launcher};

static int		check_tab(char *arg)
{
	int i;

	i = 0;
	while (i < NB_TEST)
	{
		if (!ft_strcmp(arg, g_test[i]))
			return (1 << i);
		i++;
	}
	return (0);
}

static int		parse_flag(int argc, char **argv, long *f)
{
	int		i;
	char	**arg;

	(void)argc;
	if (!(arg = ft_strsplit(argv[1], ' ')))
		return (0);
	*f = 0;
	i = 0;
	while (arg[i])
	{
		*f |= check_tab(arg[i]);
		i++;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	long	flag;
	int		i;
	int		ret;

	ft_dprintf(2, "ARG [%s]\n", argv[1]);
	flag = LONG_MAX;
	if (argv[1])
		parse_flag(argc, argv, &flag);
	ret = 0;
	i = 0;
	while (i < NB_TEST)
	{
		if (flag & (1 << i))
			ret = ((g_fun[i])() == 0) ? ret : -1;
		i++;
	}
	return (ret);
}
