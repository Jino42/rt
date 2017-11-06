/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 09:58:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 09:59:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		solve_quadratic(const float a, const float b, const float c,
							float *inter0, float *inter1)
{
	float discr;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr < 0.000005)
	{
		*inter0 = -0.5 * b / a; ///////////>
		*inter1 = *inter0;
	}
	else
	{
		float q = (b > 0) ? (-0.5 * (b + sqrt(discr))): (-0.5 * (b - sqrt(discr)));
		*inter0 = q / a;
		*inter1 = c / q;
	}
	if (*inter0 > *inter1)
	{
		float tmp;

		tmp = *inter0;
		*inter0 = *inter1;
		*inter1 = tmp;
	}
	return (true);
}
