/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_check_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 03:02:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/13 18:03:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_cl.h"

void	cl_check_err(cl_int err, const char *name)
{
	if (err != CL_SUCCESS)
	{
		ft_dprintf(2, "Error : %s (%i)\n", name, err);
		exit(EXIT_FAILURE);
	}
}
