/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 23:49:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere 	sphere_construct(const t_vector position, const float radius,
								const uint32_t color)
{
	t_sphere s;

	s.world_to_object = matrix_get_identity();
	s.color = color;
	s.position = position;
	s.radius = radius;
	s.radius2 = radius * radius;

	return (s);
}

t_plan		plan_construct(const t_vector position, const float len,
							const uint32_t color)
{
	t_plan p;

	p.world_to_object = matrix_get_identity();
	p.color = color;
	p.position = position;
	p.len = len;

	p.p0 = vector_construct(position.x - len, position.y - len, position.z);
	p.p1 = vector_construct(0, 1, 0);
	p.p2 = vector_construct(1, 0, 0);
	return (p);
}

t_cylinder	cylinder_construct(const t_vector position, const float radius,
								const uint32_t color)
{
	t_cylinder c;

	c.world_to_object = matrix_get_identity();
	c.color = color;
	c.position = position;
	c.radius = radius;
	c.radius2 = radius * radius;
	c.dir = vector_construct(0, 1, 0);

	return (c);
}

bool 		init_object(t_env *e)
{
	uint32_t	nb_sphere = 7;
	t_sphere	s[nb_sphere];
	t_list		*push;

	s[0] = sphere_construct(vector_construct(10, 10, -10), 1.7, 0x84F15E);
	s[1] = sphere_construct(vector_construct(1e5, 0, -2500), 1e5, 0xFF0000); // RIGHT WALL
	s[2] = sphere_construct(vector_construct(-1e5, 0, -2500), 1e5, 0x00FF00); // LEFT WALL
	s[3] = sphere_construct(vector_construct(0, 0, 1e5 + 100), 1e5, 0x0000FF); // BACK WALL
	s[4] = sphere_construct(vector_construct(0, 0, -1e5 - 100), 1e5, 0x005500); // FRONT WALL
	s[5] = sphere_construct(vector_construct(0, 1e5, 2500), 1e5, 0x55F0FF); // TOP WALL
	s[6] = sphere_construct(vector_construct(0, -1e5, -2500), 1e5, 0xFF5500); // DOWN WALL

	while (nb_sphere-- != 0)
	{
		if (!(push = ft_lstnew(&s[nb_sphere], sizeof(t_sphere))))
			return (false);
		ft_lstadd(&e->sphere, push);
	}
	e->light.position = vector_construct(10, 10, 0);
	e->light.intensity = 1;
	e->light.color = 0xFFFFFF;

	t_plan p;

	p = plan_construct(vector_construct(1, 1, -30), 1, 0xFF00FF);
	if (!(push = ft_lstnew(&p, sizeof(t_plan))))
		return (false);
	ft_lstadd(&e->plan, push);

	t_cylinder c;

	c = cylinder_construct(vector_construct(-10, 14, 1), 2, 0x0BFF28);
	if (!(push = ft_lstnew(&c, sizeof(t_cylinder))))
		return (false);
	ft_lstadd(&e->cylinder, push);
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


void 		update_lul(t_env *e, t_sdl *sdl)
{
	t_event		*ev;
	t_matrix	m;

	ev = &sdl->event;
	if (ev->key[SDL_SCANCODE_T])
		vector_rotate_x(&((t_plan *)e->plan->content)->p1, 0.04);
	if (ev->key[SDL_SCANCODE_Y])
		vector_rotate_y(&((t_plan *)e->plan->content)->p2, 0.04);
	if (ev->key[SDL_SCANCODE_I])
	{
		m = matrix_get_rotation_x(0.04);
		((t_cylinder *)e->cylinder->content)->world_to_object =
		matrix_get_mult_matrix(&m, &((t_cylinder *)e->cylinder->content)->world_to_object);
	}
	if (ev->key[SDL_SCANCODE_O])
	{
		m = matrix_get_rotation_y(0.04);
		((t_cylinder *)e->cylinder->content)->world_to_object =
		matrix_get_mult_matrix(&m, &((t_cylinder *)e->cylinder->content)->world_to_object);
	}
	if (ev->key[SDL_SCANCODE_P])
	{
		m = matrix_get_rotation_z(0.04);
		((t_cylinder *)e->cylinder->content)->world_to_object =
		matrix_get_mult_matrix(&m, &((t_cylinder *)e->cylinder->content)->world_to_object);
	}
}

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(&sdl->event, &e->cam);
		update_cam(&e->cam);
		update_lul(e, sdl);
		run_multi_thread(e);
		SDL_UpdateTexture(sdl->img, NULL, sdl->pix, sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		bzero(sdl->pix, sizeof(uint32_t) * sdl->height * sdl->width); //////////???????????
		SDL_RenderClear(sdl->render);
	}
}

int main(int argc, char **argv)
{
	(void)argc;(void)argv;

	t_env e;

	ft_bzero(&e, sizeof(t_env));
	if (!init_object(&e))
		return (end_of_program(&e, "Problème a l'initialisation des objets", 0));
	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	sdl_loop(&e, &e.sdl);

	end_of_program(&e, NULL, 0);
	return (0);
}
