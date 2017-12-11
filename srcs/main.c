/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/11 22:05:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_write_buffer(t_env *e, t_cl *cl)
{
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[1], CL_TRUE, 0,
							e->scene.mem_size_obj,
							e->scene.ptr_obj, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[2], CL_TRUE, 0,
							e->scene.mem_size_light,
							e->scene.ptr_light, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_light");
}

void		cl_set_arg_is_focus(const t_env *e, t_cl *cl, cl_mem *mem)
{
	uint64_t size_obj;

	size_obj = ((t_obj *)(e->scene.ptr_obj + e->mem_obj_index))->mem_size_obj;
	*mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			size_obj, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateBuffer");
	cl->err = clEnqueueWriteBuffer(cl->cq, *mem, CL_TRUE, 0,
							size_obj,
							e->scene.ptr_obj + e->mem_obj_index, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), mem);
	cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t), &size_obj);
	cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
}

void		cl_set_arg_is_not_focus(const t_env *e, t_cl *cl)
{
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t),
												&(e->scene.mem_size_obj));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
}

void		cl_set_arg(t_env *e, t_cl *cl, cl_mem *mem)
{
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->mem[0]);
	cl_check_err(cl->err, "clSetKernelArg | SDL_Pix");
	if (e->flag & F_FOCUS)
		cl_set_arg_is_focus(e, cl, mem);
	else
		cl_set_arg_is_not_focus(e, cl);
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(t_ptr_cl), &(e->p_cl));
	cl_check_err(cl->err, "clSetKernelArg | p_cl");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(t_cam), &(e->scene.cam));
	cl_check_err(cl->err, "clSetKernelArg | t_cam");
	cl->err = clSetKernelArg(cl->kernel, 5, e->scene.mem_size_obj, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->mem[2]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_light");
	cl->err = clSetKernelArg(cl->kernel, 7, sizeof(uint64_t),
											&(e->scene.mem_size_light));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_light");
	cl->err = clSetKernelArg(cl->kernel, 8, e->scene.mem_size_light, NULL);
	cl_check_err(cl->err, "clSetKernelArg | Local");
	cl->err = clSetKernelArg(cl->kernel, 9, sizeof(int), &(e->flag));
	cl_check_err(cl->err, "clSetKernelArg | flag");
}

void		cl_run_kernel(t_cl *cl)
{
	cl_event event;

	event = 0;
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
}

void		cl_render(t_env *e, t_cl *cl, t_sdl *sdl)
{
	cl_mem mem;

	mem = 0;
	cl_write_buffer(e, cl);
	cl_set_arg(e, cl, &mem);
	cl_run_kernel(cl);
	if (e->flag & F_FOCUS)
		clReleaseMemObject(mem);
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
			sizeof(uint32_t) * sdl->width * sdl->height,
			sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer sdl->pix");
}

void		sdl_loop_gpu(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(e, &sdl->event, &e->scene.cam);
		update_cam(&e->scene.cam);
		update_obj(e, sdl);
		cl_render(e, &e->cl, sdl);
		SDL_UpdateTexture(sdl->img, NULL, sdl->pix,
									sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		SDL_RenderClear(sdl->render);
	}
}

bool		flag(int64_t *f, int argc, char **argv)
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

void	debug_print_size_obj(void)
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

void	init_projection(const t_sdl *sdl, t_ptr_cl *c)
{
	c->fov = 66;
	c->invH = 1 / (float)sdl->height;
	c->invW = 1 / (float)sdl->width;
	c->ratio = (float)sdl->width / (float)sdl->height;
	c->scale = tan(M_PI * 0.5 * c->fov / 180);
}

void	cl_init_buffer(t_env *e)
{
	cl_create_buffer(&e->cl, e->sdl.height * e->sdl.width * 4);
	cl_create_buffer(&e->cl, e->scene.mem_size_obj);
	cl_create_buffer(&e->cl, e->scene.mem_size_light);
}

int		main(int argc, char **argv)
{
	t_env	e;
	int		index;

	ft_bzero(&e, sizeof(t_env));
	index = flag(&e.flag, argc, argv);
	if (!parse_scene(&e, argv[index + 1]))
		return (0);
	if (e.flag & F_DEBUG_PARSING)
		return (EXIT_SUCCESS);
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	if (e.flag & F_DEBUG_SIZE_STRUCT)
		debug_print_size_obj();
	cl_init(&e.cl, "srcs_cl/test.cl", "test", e.sdl.height * e.sdl.width);
	cl_init_buffer(&e);
	init_projection(&e.sdl, &e.p_cl);
	sdl_loop_gpu(&e, &e.sdl);
	end_of_program(&e, NULL, 0);
	return (0);
}
