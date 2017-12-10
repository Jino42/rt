/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:49:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:53:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parse.h"

static char		*arg_find(char *str, int i)
{
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == ',' || str[i] == ')')
		return (NULL);
	return (str + i);
}

char			*strchr_arg(char *str, int arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		if (str[i] == '(' && arg == 1)
			return (arg_find(str, i));
		else if (str[i] == ',' && count + 1 == arg)
			return (arg_find(str, i));
		i++;
	}
	return (NULL);
}

char			*strchr_arg_vec(char *str, int arg)
{
	int i;
	int count;

	if (arg == 1 || !arg)
		return (str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		if (str[i] == ' ' && count + 1 == arg)
			return (str + i + 1);
		i++;
	}
	return (NULL);
}

int				rt_count_number_preci(long int n)
{
	int i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
