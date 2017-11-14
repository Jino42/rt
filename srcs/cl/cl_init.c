/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:08:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/14 17:09:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_load_src(t_cl *cl, const char *path, char *k_src, size_t *src_size)
{
	int		fd;

	(void)cl;
	*src_size = 0;
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Failed to load source.\n", 2);
		exit(0);
	}
	read(fd, k_src, MAX_SOURCE_SIZE);
	*src_size = ft_strlen(k_src);
	close(fd);
}

static void		cl_create_base(t_cl *cl, const char *path)
{
	char	*k_src;
	size_t	src_size;

	k_src = (char *)ft_memalloc(MAX_SOURCE_SIZE);
	cl->err = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_platforms));
	cl_check_err(cl->err, "clGetPlatformIDs");
	cl->err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			1, &(cl->device_id), &(cl->ret_num_devices));
	cl_check_err(cl->err, "clGetDeviceIDs");
	cl->context = clCreateContext(NULL, 1,
								&(cl->device_id), NULL, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateContext");
	cl->cq = clCreateCommandQueue(cl->context,
								cl->device_id, 0, &(cl->err));
	cl_check_err(cl->err, "clCreateCommandQueue");
	cl_load_src(cl, path, k_src, &src_size);
	cl->program = clCreateProgramWithSource(cl->context,
										1, (const char **)&k_src,
			(const size_t *)&src_size, &(cl->err));
	cl_check_err(cl->err, "clCreateProgramWithSource");
	ft_strdel(&k_src);
}

static void		cl_compile_kernel(t_cl *cl)
{
	char		buffer[10000];
	size_t		len;

	cl->err = clBuildProgram(cl->program, 0, NULL, "-I.", NULL, NULL);
	if (cl->err != CL_SUCCESS)
	{
		ft_bzero(buffer, 10000);
		cl->err = clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
		if (cl->err == CL_SUCCESS)
			ft_printf("\033[31mCompiler error message :%i\033[0m\n%s", len, buffer);
		else
			ft_printf("Erreur étonnate\n");
		exit(EXIT_FAILURE);
	}
}

int				cl_init(void *a, t_cl *cl, const char *path, const char *name, const size_t global_item_size)
{
	t_env *e = a;
	cl_create_base(cl, path);
	e->a = clCreateBuffer(e->cl.context, CL_MEM_READ_WRITE,
			e->sdl.height * e->sdl.width * 4,  NULL, &(e->cl.err));
	e->b = clCreateBuffer(e->cl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			e->mem_size_obj, e->ptr_obj, &(e->cl.err));
	cl_compile_kernel(cl);
	cl->kernel = clCreateKernel(cl->program, name, &(cl->err));
	cl_check_err(cl->err, "clCreateKernel");
	cl->global_item_size = global_item_size;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
									&cl->local_item_size, NULL);
	if (cl->global_item_size % cl->local_item_size)
	{
		ft_dprintf(2, "Global_item_size %% Local item size != 0\n(%zu) %% (%zu) = %i\n",
				cl->global_item_size, cl->local_item_size,
				cl->global_item_size % cl->local_item_size);
		exit(EXIT_FAILURE);
	}
	cl_check_err(cl->err, "clGetKernelWorkGroup");
	return (1);
}
