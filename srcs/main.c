/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:36:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	debug_print_size_obj(void)
{
	ft_printf("Size t_obj        : %lu\n", sizeof(t_obj));
	ft_printf("Size t_sphere     : %lu\n", sizeof(t_sphere));
	ft_printf("Size t_plan       : %lu\n", sizeof(t_plan));
	ft_printf("Size t_ellipsoid  : %lu\n", sizeof(t_ellipsoid));
	ft_printf("Size t_cone       : %lu\n", sizeof(t_cone));
	ft_printf("Size t_paraboloid : %lu\n", sizeof(t_paraboloid));
	ft_printf("Size t_cylinder   : %lu\n", sizeof(t_cylinder));
	ft_printf("Size t_light  	 : %lu\n", sizeof(t_light));
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		index;

	ft_bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	if (!parse_scene(&e, argv[index]))
		return (0);
	if (e.flag & F_DEBUG_PARSING)
		return (EXIT_SUCCESS);
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	if (e.flag & F_DEBUG_SIZE_STRUCT)
		debug_print_size_obj();
	cl_init(&e.cl, "srcs_cl/raytracer.cl", "raytracer", e.sdl.height * e.sdl.width);
	cl_init_buffer(&e);
	init_projection(&e.sdl, &e.p_cl);
	rt_loop_gpu(&e, &e.sdl);
	end_of_program(&e, NULL, 0);
	return (0);
}
