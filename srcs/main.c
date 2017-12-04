/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/04 17:38:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere 	sphere_construct(const t_vector position,
								const float radius,
								const uint32_t color,
								const uint32_t flag,
								const float	m_specular)
{
	t_sphere obj;

	ft_bzero(&obj, sizeof(t_sphere));
	obj.mem_size_obj = sizeof(t_sphere);
	obj.id = OBJ_SPHERE;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.flag = flag;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_sphere;
	return (obj);
}

t_ellipsoid 	ellipsoid_construct(const t_vector position,
									const t_vector size,
									const float	   radius,
									const uint32_t color,
									const float m_specular)
{
	t_ellipsoid obj;

	ft_bzero(&obj, sizeof(t_ellipsoid));
	obj.mem_size_obj = sizeof(t_ellipsoid);
	obj.id = OBJ_ELLIPSOID;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.size = size;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_ellipsoid;
	return (obj);
}

t_cone 	cone_construct(const t_vector position,
								const float angle,
								const uint32_t color,
								const float m_specular)
{
	t_cone obj;

	ft_bzero(&obj, sizeof(t_cone));
	obj.mem_size_obj = sizeof(t_cone);
	obj.id = OBJ_CONE;
	obj.angle = angle;
	obj.color = color;
	obj.position = position;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_cone;
	return (obj);
}


t_paraboloid 	paraboloid_construct(const t_vector position,
										const float radius,
										const uint32_t color,
										const float m_specular)
{
	t_paraboloid obj;

	ft_bzero(&obj, sizeof(t_paraboloid));
	obj.mem_size_obj = sizeof(t_paraboloid);
	obj.id = OBJ_PARABOLOID;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_paraboloid;
	return (obj);
}

t_paraboloid_hyperbolic 	paraboloid_hyperbolic_construct(const t_vector position,
										const float radius,
										const uint32_t color,
										const float m_specular)
{
	t_paraboloid_hyperbolic obj;

	ft_bzero(&obj, sizeof(t_paraboloid_hyperbolic));
	obj.mem_size_obj = sizeof(t_paraboloid_hyperbolic);
	obj.id = OBJ_PARABOLOID_HYPERBOLIC;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_paraboloid_hyperbolic;
	return (obj);
}

t_plan		plan_construct(const t_vector position,
							const uint32_t color,
							const float m_specular)
{
	t_plan obj;

	ft_bzero(&obj, sizeof(t_plan));
	obj.mem_size_obj = sizeof(t_plan);
	obj.id = OBJ_PLANE;
	obj.color = color;
	obj.position = position;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.m_specular = m_specular;

	obj.normal = vector_construct(0, 0, 1);

	obj.intersect = &intersection_plane;
	return (obj);
}

t_cylinder	cylinder_construct(const t_vector position,
								const float radius,
								const uint32_t color,
								const float m_specular)
{
	t_cylinder obj;

	ft_bzero(&obj, sizeof(t_cylinder));
	obj.mem_size_obj = sizeof(t_cylinder);
	obj.id = OBJ_CYLINDER;
	obj.color = color;
	obj.position = position;
	obj.radius = radius;
	obj.radius2 = radius * radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.m_specular = m_specular;

	obj.intersect = &intersection_cylinder;
	return (obj);
}

t_light	 	light_construct(uint8_t type, const t_vector position, float intensity, const uint32_t color, const float radius)
{
	t_light		obj;

	obj.type = type;
	obj.position = position;
	obj.color = color;
	obj.intensity = intensity;
	obj.radius = radius;
	obj.radius = radius * radius;
	return (obj);
}

bool 		init_object(t_env *e)
{
	uint32_t	nb_sphere = 8;
	t_sphere	s[nb_sphere];
	t_list		*push;

	s[0] = sphere_construct(vector_construct(20, 20, 0), 0.5, 0x84F15E, 0, 0);
	s[1] = sphere_construct(vector_construct(1e5, 0, -2500), 1e5, 0xFF0000, 0, 0); // RIGHT WALL
	s[2] = sphere_construct(vector_construct(-1e5, 0, -2500), 1e5, 0x00FF00, 0, 0); // LEFT WALL
	s[3] = sphere_construct(vector_construct(0, 0, 1e5 + 100), 1e5, 0x0000FF, 0, 0); // BACK WALL
	s[4] = sphere_construct(vector_construct(0, 0, -1e5 - 100), 1e5, 0x005500, 0, 0); // FRONT WALL
	s[5] = sphere_construct(vector_construct(0, 1e5, 2500), 1e5, 0x55F0FF, 0, 0); // TOP WALL
	s[6] = sphere_construct(vector_construct(0, -1e5, -2500), 1e5, 0xFF5500, 0, 0); // DOWN WALL
	s[7] = sphere_construct(vector_construct(10, 10, 10), 0.1, 0xFFFFFF, F_ISLIGHT, 0);
//	s[8] = sphere_construct(vector_construct(20, 20, 0), 0.1, 0xFFFFFF, F_ISLIGHT);

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

	/*		TEST PTR OBJ SPHERE 		*/

	tn = e->ptr_obj;
	ti = 0;
	while (ti < 8)
	{
		to=tn;
		vector_string(&to->position);
		printf("Size obj : %llu\n", to->mem_size_obj);
		printf("Id   obj : %i\n", to->id);
		printf("Colorobj : %i\n", to->color);
		printf("WTF! ! ! ! : %lu\n", sizeof(to->intersect));
		tn+=to->mem_size_obj;
		ti++;
	}
	printf("Sizeof t_sphere : %lu\n", sizeof(t_sphere));
	printf("Sizeof t_obj    : %lu\n", sizeof(t_obj));

	t_plan p;

	p = plan_construct(vector_construct(1, 1, -30), 0xFF00FF, 2);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_plan));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&p, e->mem_size_obj, sizeof(t_plan));
	vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);

	e->mem_size_obj += sizeof(t_plan);

	if (!(push = ft_lstnew(&p, sizeof(t_plan))))
		return (false);
	ft_lstinsert(&e->obj, push);

	t_cylinder c;

	c = cylinder_construct(vector_construct(5, 5, 5), 2, 0x0BFF28, 13);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_cylinder));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&c, e->mem_size_obj, sizeof(t_cylinder));
	vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);

	e->mem_size_obj += sizeof(t_cylinder);

	if (!(push = ft_lstnew(&c, sizeof(t_cylinder))))
		return (false);
	ft_lstinsert(&e->obj, push);

	t_paraboloid paraboloid;

	paraboloid = paraboloid_construct(vector_construct(-5, -4, -8), 2, 0xF28FB0, 7);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_paraboloid));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&paraboloid, e->mem_size_obj, sizeof(t_paraboloid));
	vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);

	e->mem_size_obj += sizeof(t_paraboloid);

	if (!(push = ft_lstnew(&paraboloid, sizeof(t_paraboloid))))
		return (false);
	ft_lstinsert(&e->obj, push);



	t_cone cone;
	cone = cone_construct(vector_construct(5, 5, 5), 0.45f, 0xbe6226, 8);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_cone));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&cone, e->mem_size_obj, sizeof(t_cone));
		vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);
	ft_printf("Cone : ID[%i] | Size in mem %li\n", cone.id, e->mem_size_obj);
	e->mem_size_obj += sizeof(t_cone);

	if (!(push = ft_lstnew(&cone, sizeof(t_cone))))
		return (false);
	ft_lstinsert(&e->obj, push);

	t_ellipsoid ellipsoid;
	ellipsoid = ellipsoid_construct(vector_construct(1, 1, 1), vector_construct(1, 1, 1),1, 0x225be6, 4);

	e->ptr_obj = ft_memrealloc(e->ptr_obj, e->mem_size_obj, e->mem_size_obj + sizeof(t_ellipsoid));
	e->ptr_obj = ft_memcpy_offset(e->ptr_obj, (void *)&ellipsoid, e->mem_size_obj, sizeof(t_ellipsoid));
	vector_string(&((t_obj*)(e->ptr_obj + e->mem_size_obj))->position);

	e->mem_size_obj += sizeof(t_ellipsoid);

	if (!(push = ft_lstnew(&ellipsoid, sizeof(t_ellipsoid))))
		return (false);
	ft_lstinsert(&e->obj, push);


/*|
**|============================================================================|
**|								    {LIGHT} 								   |
**|============================================================================|
*/

	t_light light;
	light = light_construct(LIGHT_BASIC, vector_construct(10, 10, 10), 0.66, 0xFFFFFF, 10);

	e->ptr_light = ft_memrealloc(e->ptr_light, e->mem_size_light, e->mem_size_light + sizeof(t_light));
	e->ptr_light = ft_memcpy_offset(e->ptr_light, (void *)&light, e->mem_size_light, sizeof(t_light));

	e->mem_size_light += sizeof(t_light);
	light = light_construct(LIGHT_BASIC, vector_construct(-10, 10, 10), 0.33, 0xFFFFFF, 2);

	e->ptr_light = ft_memrealloc(e->ptr_light, e->mem_size_light, e->mem_size_light + sizeof(t_light));
	e->ptr_light = ft_memcpy_offset(e->ptr_light, (void *)&light, e->mem_size_light, sizeof(t_light));

	e->mem_size_light += sizeof(t_light);

	ft_printf("Size light ; %u\n", e->mem_size_light);

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
		e->count.time = e->fps.delta_time;
		sdl_update_event(sdl, &sdl->event);
		event_cam(e, &sdl->event, &e->cam);
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

			//------------>Write IMG
	/*cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
							sizeof(uint32_t) * sdl->width * sdl->height,
							sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer");*/

			//------------>Write OBJ
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[1], CL_TRUE, 0,
							e->mem_size_obj,
							e->ptr_obj, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[2], CL_TRUE, 0,
							e->mem_size_light,
							e->ptr_light, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_light");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[3], CL_TRUE, 0,
							sizeof(t_count),
							&e->count, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer struct count");

	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->mem[0]);
	cl_check_err(cl->err, "clSetKernelArg | SDL_Pix");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t), &(e->mem_size_obj));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(t_ptr_cl), &(e->p_cl));
	cl_check_err(cl->err, "clSetKernelArg | p_cl");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(t_cam), &(e->cam));
	cl_check_err(cl->err, "clSetKernelArg | t_cam");
	cl->err = clSetKernelArg(cl->kernel, 5, e->mem_size_obj, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->mem[2]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_light");
	cl->err = clSetKernelArg(cl->kernel, 7, sizeof(uint64_t), &(e->mem_size_light));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_light");
	cl->err = clSetKernelArg(cl->kernel, 8, e->mem_size_light, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 9, sizeof(cl_mem), &cl->mem[3]);
	cl_check_err(cl->err, "clSetKernelArg | count struct");
	/*cl->err = clSetKernelArg(cl->kernel, 6, sizeof(int), &e->flag);
	cl_check_err(cl->err, "clSetKernelArg | flag");*/
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
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
			sizeof(uint32_t) * sdl->width * sdl->height,
			sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer sdl->pix");
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[3], CL_TRUE, 0,
			sizeof(t_count),
			&e->count, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer struct count");

	/*			      */
}

void		sdl_loop_gpu(t_env *e, t_sdl *sdl)
{
	t_count *c;

	c = &e->count;
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		e->count.time = e->fps.delta_time;
		event_cam(e, &sdl->event, &e->cam);
		update_cam(&e->cam);
		update_obj(e, sdl);

		e->count.nb_try = 0;
		e->count.nb_hit = 0;
		cl_render(e, &e->cl, sdl);
		//run_multi_thread(e);
		//ft_printf("Resultat en [%.2f]\nNb_obj [%li] for [%li] ray\n[%li] / [%li]\n",
		//			c->time,c->nb_obj,c->nb_ray,c->nb_hit,c->nb_try);
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
		else if (ft_strequ(argv[i], "-debug"))
			*f |= F_DEBUG;
		else if (ft_strequ(argv[i], "-debug_cl"))
			*f |= F_DEBUG_CL;
		else if (ft_strequ(argv[i], "-debug_s"))
			*f |= F_DEBUG_SIZE_STRUCT;
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
	if (e.flag & F_DEBUG_SIZE_STRUCT)
	{
		printf("Size t_obj        : %lu\n", sizeof(t_obj));
		printf("Size t_sphere     : %lu\n", sizeof(t_sphere));
		printf("Size t_plan       : %lu\n", sizeof(t_plan));
		printf("Size t_ellipsoid  : %lu\n", sizeof(t_ellipsoid));
			printf("Size t_cone       : %lu\n", sizeof(t_cone));
		printf("Size t_paraboloid : %lu\n", sizeof(t_paraboloid));
		printf("Size t_cylinder   : %lu\n", sizeof(t_cylinder));
	}
	e.cam.speed_rotate = 4;
	e.cam.speed = 32;
	if (!(e.flag & F_CPU))
	{
		cl_init(&e.cl, "srcs_cl/test.cl", "test", e.sdl.height * e.sdl.width);
		cl_create_buffer(&e.cl, e.sdl.height * e.sdl.width * 4);
		cl_create_buffer(&e.cl, e.mem_size_obj);
		cl_create_buffer(&e.cl, e.mem_size_light);
		cl_create_buffer(&e.cl, sizeof(t_count));
		t_ptr_cl *c = &e.p_cl;
		c->fov = 66;
		c->invH = 1 / (float)e.sdl.height;
		c->invW = 1 / (float)e.sdl.width;
		c->ratio = (float)e.sdl.width / (float)e.sdl.height;
		c->scale = tan(M_PI * 0.5 * c->fov / 180);
		e.count.nb_obj = e.obj_len;
		e.count.nb_ray = e.sdl.height * e.sdl.width;
	}
	e.mem_obj_index = 896;
	if (e.flag & F_CPU)
		sdl_loop(&e, &e.sdl);
	else
		sdl_loop_gpu(&e, &e.sdl);

	end_of_program(&e, NULL, 0);
	return (0);
}
