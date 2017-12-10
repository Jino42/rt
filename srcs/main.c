/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 18:20:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		event_cam(e, &sdl->event, &e->scene.cam);
		update_cam(&e->scene.cam);
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
							e->scene.mem_size_obj,
							e->scene.ptr_obj, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[2], CL_TRUE, 0,
							e->scene.mem_size_light,
							e->scene.ptr_light, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_light");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[3], CL_TRUE, 0,
							sizeof(t_count),
							&e->count, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer struct count");

	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->mem[0]);
	cl_check_err(cl->err, "clSetKernelArg | SDL_Pix");
	cl_mem mem = 0;
	if (e->flag & F_FOCUS)
	{
		uint64_t size_obj = ((t_obj *)(e->scene.ptr_obj + e->mem_obj_index))->mem_size_obj;
		mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				size_obj,  NULL, &(cl->err));
		cl_check_err(cl->err, "clCreateBuffer");
		cl->err = clEnqueueWriteBuffer(cl->cq, mem, CL_TRUE, 0,
								size_obj,
								e->scene.ptr_obj + e->mem_obj_index, 0, NULL, NULL);
		cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
		cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &mem);
		cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
		cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t), &size_obj);
		cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
	}
	else
	{
		cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
		cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
		cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t), &(e->scene.mem_size_obj));
		cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
	}
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(t_ptr_cl), &(e->p_cl));
	cl_check_err(cl->err, "clSetKernelArg | p_cl");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(t_cam), &(e->scene.cam));
	cl_check_err(cl->err, "clSetKernelArg | t_cam");
	cl->err = clSetKernelArg(cl->kernel, 5, e->scene.mem_size_obj, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->mem[2]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_light");
	cl->err = clSetKernelArg(cl->kernel, 7, sizeof(uint64_t), &(e->scene.mem_size_light));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_light");
	cl->err = clSetKernelArg(cl->kernel, 8, e->scene.mem_size_light, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 9, sizeof(cl_mem), &cl->mem[3]);
	cl_check_err(cl->err, "clSetKernelArg | count struct");
	cl->err = clSetKernelArg(cl->kernel, 10, sizeof(int), &(e->flag));
	cl_check_err(cl->err, "clSetKernelArg | flag");
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

	if (e->flag & F_FOCUS)
		clReleaseMemObject(mem);
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
		event_cam(e, &sdl->event, &e->scene.cam);
		update_cam(&e->scene.cam);
		update_obj(e, sdl);

		e->count.nb_try = 0;
		e->count.nb_hit = 0;
		cl_render(e, &e->cl, sdl);
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
		else if (ft_strequ(argv[i], "-debug_s"))
			*f |= F_DEBUG_SIZE_STRUCT;
		else if (ft_strequ(argv[i], "-debug_p"))
			*f |= F_DEBUG_PARSING;
		else
			return (i);
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	(void)argc;(void)argv;

	t_env e;

	int index;
	ft_bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	if (!parse_scene(&e, argv[index + 1]))
		return (0);
	if (e.flag & F_DEBUG_PARSING)
		return (EXIT_SUCCESS);
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	t_sphere *sphere;
	int i = 0;
	while (i < 7)
	{
		sphere = e.scene.ptr_obj + (i * sizeof(t_sphere));
		ft_printf("Sphere : %i\n", i);
		vector_string(&sphere->position);
		printf("Raypn %.2f\n", sphere->radius);
		i++;
	}
	if (e.flag & F_DEBUG_SIZE_STRUCT)
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
	e.scene.cam.speed_rotate = 4;
	e.scene.cam.speed = 32;
	if (!(e.flag & F_CPU))
	{
		cl_init(&e.cl, "srcs_cl/test.cl", "test", e.sdl.height * e.sdl.width);
		cl_create_buffer(&e.cl, e.sdl.height * e.sdl.width * 4);
		cl_create_buffer(&e.cl, e.scene.mem_size_obj);
		cl_create_buffer(&e.cl, e.scene.mem_size_light);
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
	e.mem_obj_index = 1128;
	if (e.flag & F_CPU)
		sdl_loop(&e, &e.sdl);
	else
		sdl_loop_gpu(&e, &e.sdl);

	end_of_program(&e, NULL, 0);
	return (0);
}
