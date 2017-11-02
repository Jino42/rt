/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:21:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/02 15:22:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		event_cam(t_event *event, t_cam *cam)
{
	t_vector	dir;

	float speed = 0.07; //speed delta_time ?
	if (event->key[SDL_SCANCODE_UP])
	{
		dir = vector_construct(0, 0, -1);
		dir = matrix_get_mult_vector(&cam->camera_to_world, &dir);
		vector_add(&cam->position, &dir);
	}
	if (event->key[SDL_SCANCODE_DOWN])
	{
		dir = vector_construct(0, 0, 1);
		dir = matrix_get_mult_vector(&cam->camera_to_world, &dir);
		vector_add(&cam->position, &dir);
	}
	if (event->key[SDL_SCANCODE_LEFT])
		cam->angle.y += speed;
	if (event->key[SDL_SCANCODE_RIGHT])
		cam->angle.y -= speed;
	if (event->key[SDL_SCANCODE_W])
		cam->angle.x += speed;
	if (event->key[SDL_SCANCODE_S])
		cam->angle.x -= speed;
	if (event->key[SDL_SCANCODE_A])
		cam->angle.z += speed;
	if (event->key[SDL_SCANCODE_D])
		cam->angle.z -= speed;
}
