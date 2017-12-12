/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:10:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:30:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CL_H
# define RT_CL_H

# include "../libft/includes/libft.h"
# include <OpenCL/opencl.h>

# define MAX_SOURCE_SIZE (30000)
# define CL_ERROR_LEN_BUFFER 17000

typedef struct	s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	cq;
	size_t				nb_mem;
	cl_mem				*mem;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				err;
	size_t				global_item_size;
	size_t				local_item_size;

	char				*path;
}				t_cl;

void 					cl_check_err(cl_int err, const char *name);
void 					cl_end(t_cl *cl);
int						cl_init(t_cl *cl, const char *path, const char *name, const size_t global_item_size);
bool					cl_create_buffer(t_cl *cl, size_t size);

#endif
