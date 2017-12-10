/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:49:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:57:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parse.h"

bool			get_float(char *str, float *nb)
{
	int			i;
	int			preci;
	bool		in;

	*nb = ft_atoi(str);
	in = false;
	preci = 0;
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '.')
		{
			if (in)
				return (false);
			in = true;
			preci = ft_atoi(str + i + 1);
			*nb += (preci / pow(10, rt_count_number_preci(preci)));
		}
		i++;
	}
	return (true);
}

bool			get_radius(char *str, float *radius, float *radius2)
{
	int			i;
	int			preci;
	bool		in;

	*radius = ft_atoi(str);
	in = false;
	preci = 0;
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '.')
		{
			if (in)
				return (false);
			in = true;
			preci = ft_atoi(str + i + 1);
			*radius += (preci / pow(10, rt_count_number_preci(preci)));
		}
		i++;
	}
	*radius2 = *radius * *radius;
	return (true);
}

bool			get_hexa(char *str, uint32_t *nb)
{
	*nb = ft_atoi_base(str, 16);
	return (true);
}

bool			get_vec(char *str, t_vector *vec)
{
	if (!str)
		return (false);
	if (nb_of_arg(str, ' ', ",)") != 3)
		return (false);
	if (!get_float(strchr_arg_vec(str, 1), &vec->x) ||
		!get_float(strchr_arg_vec(str, 2), &vec->y) ||
		!get_float(strchr_arg_vec(str, 3), &vec->z))
		return (false);
	return (true);
}
