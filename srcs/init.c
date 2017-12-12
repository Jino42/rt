/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:55:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:29:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_projection(const t_sdl *sdl, t_ptr_cl *c)
{
	c->fov = 66;
	c->inv_h = 1 / (float)sdl->height;
	c->inv_w = 1 / (float)sdl->width;
	c->ratio = (float)sdl->width / (float)sdl->height;
	c->scale = tan(M_PI * 0.5 * c->fov / 180);
}

void	cl_init_buffer(t_env *e)
{
	cl_create_buffer(&e->cl, e->sdl.height * e->sdl.width * 4);
	cl_create_buffer(&e->cl, e->scene.mem_size_obj);
	cl_create_buffer(&e->cl, e->scene.mem_size_light);
}

int		flag(int64_t *f, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-debug_s"))
			*f |= F_DEBUG_SIZE_STRUCT;
		else if (ft_strequ(argv[i], "-debug_p"))
			*f |= F_DEBUG_PARSING;
		else
			return (i);
		i++;
	}
	return (i);
}
