/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:21:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/15 21:14:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		event_cam(t_env *e, t_event *event, t_cam *cam)
{
	t_vector	dir;

	if (event->key[SDL_SCANCODE_UP])
	{
		dir = vector_construct(0, 0, -cam->speed * e->fps.delta_time);
		dir = matrix_get_mult_vector(&cam->camera_to_world, &dir);
		vector_add(&cam->position, &dir);
	}
	if (event->key[SDL_SCANCODE_DOWN])
	{
		dir = vector_construct(0, 0, cam->speed * e->fps.delta_time);
		dir = matrix_get_mult_vector(&cam->camera_to_world, &dir);
		vector_add(&cam->position, &dir);
	}
	if (event->key[SDL_SCANCODE_LEFT])
		cam->angle.y += cam->speed_rotate * e->fps.delta_time;
	if (event->key[SDL_SCANCODE_RIGHT])
		cam->angle.y -= cam->speed_rotate * e->fps.delta_time;
	if (event->key[SDL_SCANCODE_W])
		cam->angle.x += cam->speed_rotate * e->fps.delta_time;
	if (event->key[SDL_SCANCODE_S])
		cam->angle.x -= cam->speed_rotate * e->fps.delta_time;
	if (event->key[SDL_SCANCODE_A])
		cam->angle.z += cam->speed_rotate * e->fps.delta_time;
	if (event->key[SDL_SCANCODE_D])
		cam->angle.z -= cam->speed_rotate * e->fps.delta_time;
}
