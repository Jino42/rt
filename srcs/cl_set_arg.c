/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_set_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:18:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:22:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_write_buffer(t_env *e, t_cl *cl)
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

static void		cl_set_arg_is_focus(const t_env *e, t_cl *cl, cl_mem *mem)
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

static void		cl_set_arg_is_not_focus(const t_env *e, t_cl *cl)
{
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
	cl_check_err(cl->err, "clSetKernelArg | ptr_obj");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(uint64_t),
												&(e->scene.mem_size_obj));
	cl_check_err(cl->err, "clSetKernelArg | mem_size_obj");
}

void			cl_set_arg(t_env *e, t_cl *cl, cl_mem *mem)
{
	cl_write_buffer(e, cl);
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
