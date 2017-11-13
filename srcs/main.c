/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/13 18:41:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere 	sphere_construct(const t_vector position,
								const float radius,
								const uint32_t color)
{
	t_sphere obj;

	obj.id = OBJ_SPHERE;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_sphere;
	return (obj);
}

t_ellipsoid 	ellipsoid_construct(const t_vector position,
									const t_vector size,
									const float	   radius,
									const uint32_t color)
{
	t_ellipsoid obj;

	obj.id = OBJ_ELLIPSOID;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.size = size;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_ellipsoid;
	return (obj);
}

t_cone 	cone_construct(const t_vector position,
								const uint32_t color)
{
	t_cone obj;

	obj.id = OBJ_CONE;
	obj.color = color;
	obj.position = position;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_cone;
	return (obj);
}


t_paraboloid 	paraboloid_construct(const t_vector position,
										const float radius,
										const uint32_t color)
{
	t_paraboloid obj;

	obj.id = OBJ_PARABOLOID;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_paraboloid;
	return (obj);
}

t_paraboloid_hyperbolic 	paraboloid_hyperbolic_construct(const t_vector position,
										const float radius,
										const uint32_t color)
{
	t_paraboloid_hyperbolic obj;

	obj.id = OBJ_PARABOLOID_HYPERBOLIC;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_paraboloid_hyperbolic;
	return (obj);
}

t_plan		plan_construct(const t_vector position,
							const float len,
							const uint32_t color)
{
	t_plan p;

	p.id = OBJ_PLANE;
	p.color = color;
	p.position = position;
	p.len = len;
	p.rotate_speed = 1.5;
	p.speed = 5;

	p.world_to_object = matrix_get_identity();
	p.translation = matrix_get_identity();

	p.p0 = vector_construct(position.x - len, position.y - len, position.z);
	p.p1 = vector_construct(0, 1, 0);
	p.p2 = vector_construct(1, 0, 0);

	p.intersect = &intersection_plane;
	return (p);
}

t_cylinder	cylinder_construct(const t_vector position,
								const float radius,
								const uint32_t color)
{
	t_cylinder c;

	c.id = OBJ_CYLINDER;
	c.color = color;
	c.position = position;
	c.radius = radius;
	c.radius2 = radius * radius;
	c.rotate_speed = 1.5;
	c.speed = 5;

	c.world_to_object = matrix_get_identity();
	c.translation = matrix_get_identity();

	c.intersect = &intersection_cylinder;
	return (c);
}

bool 		init_object(t_env *e)
{
	uint32_t	nb_sphere = 8;
	t_sphere	s[nb_sphere];
	t_list		*push;

	s[0] = sphere_construct(vector_construct(10, 10, -10), 1.7, 0x84F15E);
	s[1] = sphere_construct(vector_construct(1e5, 0, -2500), 1e5, 0xFF0000); // RIGHT WALL
	s[2] = sphere_construct(vector_construct(-1e5, 0, -2500), 1e5, 0x00FF00); // LEFT WALL
	s[3] = sphere_construct(vector_construct(0, 0, 1e5 + 100), 1e5, 0x0000FF); // BACK WALL
	s[4] = sphere_construct(vector_construct(0, 0, -1e5 - 100), 1e5, 0x005500); // FRONT WALL
	s[5] = sphere_construct(vector_construct(0, 1e5, 2500), 1e5, 0x55F0FF); // TOP WALL
	s[6] = sphere_construct(vector_construct(0, -1e5, -2500), 1e5, 0xFF5500); // DOWN WALL
	s[7] = sphere_construct(vector_construct(10, 10, 0), 0.1, 0xFFFFFF);

	while (nb_sphere-- != 0)
	{
		if (!(push = ft_lstnew(&s[nb_sphere], sizeof(t_sphere))))
			return (false);
		ft_lstinsert(&e->obj, push);
	}
	e->light.position = vector_construct(10, 10, 0);
	e->light.intensity = 1;
	e->light.color = 0xFFFFFF;

/*
	t_plan p;

	p = plan_construct(vector_construct(1, 1, -30), 1, 0xFF00FF);
	if (!(push = ft_lstnew(&p, sizeof(t_plan))))
		return (false);
	ft_lstinsert(&e->obj, push);

	t_cylinder c;

	c = cylinder_construct(vector_construct(5, 5, 5), 2, 0x0BFF28);
	if (!(push = ft_lstnew(&c, sizeof(t_cylinder))))
		return (false);
	ft_lstinsert(&e->obj, push);

	t_paraboloid paraboloid;
	paraboloid = paraboloid_construct(vector_construct(-5, -4, -8), 2, 0xF28FB0);
	if (!(push = ft_lstnew(&paraboloid, sizeof(t_paraboloid))))
		return (false);
	ft_lstinsert(&e->obj, push);
*/
	t_ellipsoid ellipsoid;
	ellipsoid = ellipsoid_construct(vector_construct(-5, -4, -20), vector_construct(10, 2, 30),10, 0x225be6);
	if (!(push = ft_lstnew(&ellipsoid, sizeof(t_ellipsoid))))
		return (false);
	ft_lstinsert(&e->obj, push);
/*
	t_cone cone;
	cone = cone_construct(vector_construct(-5, -4, -20), 0xbe6226);
	if (!(push = ft_lstnew(&cone, sizeof(t_cone))))
		return (false);
	ft_lstinsert(&e->obj, push);
	*/

	e->obj_len = ft_lstlen(e->obj);
	return (true);
}

void 		run_multi_thread(t_env *e)
{
	t_arg_thread	arg_thread[NB_THREAD];
	pthread_t		thread[NB_THREAD];
	int				i;

	i = 0;
	while (i < NB_THREAD)
	{
		arg_thread[i].e = e;
		arg_thread[i].start_y = HEIGHT / NB_THREAD * i;
		arg_thread[i].end_y = arg_thread[i].start_y + HEIGHT / NB_THREAD;
		pthread_create(&thread[i], NULL, foreachpix, (void *)&arg_thread[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(&sdl->event, &e->cam);
		update_cam(&e->cam);
		update_obj(e, sdl);
		run_multi_thread(e);
		SDL_UpdateTexture(sdl->img, NULL, sdl->pix, sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		bzero(sdl->pix, sizeof(uint32_t) * sdl->height * sdl->width); //////////???????????
		SDL_RenderClear(sdl->render);
	}
}

void 		cl_render(t_cl *cl, t_sdl *sdl)
{
	/* SET KERNEL ARGS*/
	cl_event event = 0;
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
							sizeof(uint32_t) * sdl->width * sdl->height,
							sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem[0]));
	cl_check_err(cl->err, "clSetKernelArg");
	/* RUN KERNEL     */
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
										&cl->global_item_size,
										&cl->local_item_size,
										0, NULL, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clWaitForEvents(1, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
	clReleaseEvent(event);
	/* GET RET        */
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[0], CL_FALSE, 0,
			sizeof(uint32_t) * sdl->width * sdl->height,
			sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");
	/*			      */
}

void		sdl_loop_gpu(t_env *e, t_sdl *sdl)
{

	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(&sdl->event, &e->cam);
		update_cam(&e->cam);
		update_obj(e, sdl);

		cl_render(&e->cl, sdl);
		//run_multi_thread(e);

		SDL_UpdateTexture(sdl->img, NULL, sdl->pix, sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		bzero(sdl->pix, sizeof(uint32_t) * sdl->height * sdl->width); //////////???????????
		SDL_RenderClear(sdl->render);
	}
}

bool		flag(int64_t *f, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-cpu"))
			*f |= F_CPU;
		else
			return (false);
		i++;
	}
	return (true);
}

int main(int argc, char **argv)
{
	(void)argc;(void)argv;

	t_env e;

	ft_bzero(&e, sizeof(t_env));
	if (!flag(&e.flag, argc, argv))
		return (end_of_program(&e, "usage: ./rt [-cpu]", 0));
	if (!init_object(&e))
		return (end_of_program(&e, "Problème a l'initialisation des objets", 0));
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	if (!(e.flag & F_CPU))
	{
		cl_init(&e.cl, "test.cl", "test", e.sdl.height * e.sdl.width);
		cl_create_buffer(&e.cl, e.sdl.height * e.sdl.width * 4);
	}
	if (e.flag & F_CPU)
		sdl_loop(&e, &e.sdl);
	else
		sdl_loop_gpu(&e, &e.sdl);

	end_of_program(&e, NULL, 0);
	return (0);
}
