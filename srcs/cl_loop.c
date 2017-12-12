/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:57:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:22:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_run_kernel(t_cl *cl)
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

static void		cl_render(t_env *e, t_cl *cl, t_sdl *sdl)
{
	cl_mem mem;

	mem = 0;
	cl_set_arg(e, cl, &mem);
	cl_run_kernel(cl);
	if (e->flag & F_FOCUS)
		clReleaseMemObject(mem);
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
			sizeof(uint32_t) * sdl->width * sdl->height,
			sdl->pix, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer sdl->pix");
}

void			rt_loop_gpu(t_env *e, t_sdl *sdl)
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
