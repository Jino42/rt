/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/14 17:21:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere 	sphere_construct(const t_vector position,
								const float radius,
								const uint32_t color)
{
	t_sphere obj;

	obj.mem_size_obj = sizeof(t_sphere);
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

	obj.mem_size_obj = sizeof(t_ellipsoid);
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

	obj.mem_size_obj = sizeof(t_cone);
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

	obj.mem_size_obj = sizeof(t_paraboloid);
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

	obj.mem_size_obj = sizeof(t_paraboloid_hyperbolic);
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
	t_plan obj;

	obj.mem_size_obj = sizeof(t_plan);
	obj.id = OBJ_PLANE;
	obj.color = color;
	obj.position = position;
	obj.len = len;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.p0 = vector_construct(position.x - len, position.y - len, position.z);
	obj.p1 = vector_construct(0, 1, 0);
	obj.p2 = vector_construct(1, 0, 0);

	obj.intersect = &intersection_plane;
	return (obj);
}

t_cylinder	cylinder_construct(const t_vector position,
								const float radius,
								const uint32_t color)
{
	t_cylinder obj;

	obj.mem_size_obj = sizeof(t_cylinder);
	obj.id = OBJ_CYLINDER;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;

	obj.world_to_object = matrix_get_identity();
	obj.translation = matrix_get_identity();

	obj.intersect = &intersection_cylinder;
	return (obj);
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

	void *tn;
	t_obj *to;
	int ti;

	while (nb_sphere-- != 0)
	{
		//e->mem_size_obj += sizeof(t_sphere);
		ft_printf("Avant realloc\n");
		if (!(e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_sphere))))
		//if (!(e->ptr_obj = realloc(e->ptr_obj, e->mem_size_obj)))
			return (end_of_program(e, "malloc failed", 0));
		ft_printf("Avant Copy %llu\n", e->mem_size_obj);
		if (!(e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&s[nb_sphere], e->mem_size_obj, sizeof(t_sphere))))
			return (end_of_program(e, "memcpy return Null", 0));
		e->mem_size_obj += sizeof(t_sphere);

		ft_printf("Apres copy\n");
		if (!(push = ft_lstnew(&s[nb_sphere], sizeof(t_sphere))))
			return (false);
		ft_lstinsert(&e->obj, push);
		to = e->ptr_obj + e->mem_size_obj - sizeof(t_sphere);
		printf("%llu\n%hhi\n", to->mem_size_obj, to->id);
	}
	e->light.position = vector_construct(10, 10, 0);
	e->light.intensity = 1;
	e->light.color = 0xFFFFFF;

	/*		TEST PTR OBJ SPHERE 		*/

	tn = e->ptr_obj;
	ti = 0;
	while (ti < 8)
	{
		to=tn;
		vector_string(&to->position);
		tn+=to->mem_size_obj;
		ti++;
	}
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
	ellipsoid = ellipsoid_construct(vector_construct(-10, -4, -20), vector_construct(2, 20, 3),10, 0x225be6);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_ellipsoid));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&ellipsoid, e->mem_size_obj, sizeof(t_ellipsoid));
	vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);

	e->mem_size_obj += sizeof(t_ellipsoid);


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

void 		cl_render(t_env *e, t_cl *cl, t_sdl *sdl)
{
	cl_event event = 0;

	/* SET KERNEL ARGS*/
/*
			//------------>Write IMG
	cl->err = clEnqueueWriteBuffer(cl->cq, e->a, CL_TRUE, 0,
							sizeof(uint32_t) * sdl->width * sdl->height,
							sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer");

			//------------>Write OBJ
	cl->err = clEnqueueWriteBuffer(cl->cq, e->b, CL_TRUE, 0,
							e->mem_size_obj,
							e->ptr_obj, 0, NULL, NULL);
	//printf("HORS DE LA | !! \n");vector_string(&(((t_obj*)e->ptr_obj)->position));
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	*/


	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &e->a);
	cl_check_err(cl->err, "clSetKernelArg | SDL_Pix");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &e->b);
	cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t), &(e->mem_size_obj));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
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
	cl->err = clEnqueueReadBuffer(cl->cq, e->a, CL_TRUE, 0,
			sizeof(uint32_t) * sdl->width * sdl->height,
			sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");


	int i = 0;
	while (i++ < 200)
		printf("%i", *((char *)(e->ptr_obj + i)));
		printf("\n");

		printf("\nAPRES\n");

	cl->err = clEnqueueReadBuffer(cl->cq, e->a, CL_TRUE, 0,
			e->mem_size_obj,
			e->ptr_obj, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");

	i = 0;
	while (i++ < 200)
		printf("%i", *((char *)(e->ptr_obj + i)));
		printf("\n");

	exit(0);

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

		cl_render(e, &e->cl, sdl);
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
		cl_init((void *)&e, &e.cl, "test.cl", "test", e.sdl.height * e.sdl.width);
		/*cl_create_buffer(&e.cl, e.sdl.height * e.sdl.width * 4);
		cl_create_buffer(&e.cl, e.mem_size_obj);*/
		/*e.a = clCreateBuffer(e.cl.context, CL_MEM_READ_WRITE,
				e.sdl.height * e.sdl.width * 4,  NULL, &(e.cl.err));
		e.b = clCreateBuffer(e.cl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
				e.mem_size_obj, e.ptr_obj, &(e.cl.err));
		*/
	}
	if (e.flag & F_CPU)
		sdl_loop(&e, &e.sdl);
	else
		sdl_loop_gpu(&e, &e.sdl);

	end_of_program(&e, NULL, 0);
	return (0);
}
