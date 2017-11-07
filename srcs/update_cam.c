/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:25:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/07 16:24:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		update_cam(t_cam *cam)
{
	t_matrix rot_x;
	t_matrix rot_y;
	t_matrix rot_z;

	rot_x = matrix_get_rotation_x(cam->angle.x);
	rot_y = matrix_get_rotation_y(cam->angle.y);
	rot_z = matrix_get_rotation_z(cam->angle.z);
	cam->camera_to_world = matrix_get_mult_matrix(&rot_x, &rot_y);
	cam->camera_to_world = matrix_get_mult_matrix(&cam->camera_to_world, &rot_z);
}
