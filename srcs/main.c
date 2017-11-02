/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/02 20:39:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sphere 	sphere_construct(const t_vector position, const float radius,
								const uint32_t color)
{
	t_sphere s;

	s.color = color;
	s.position = position;
	s.radius = radius;

	return (s);
}

bool 		init_object(t_env *e)
{
	uint32_t	nb_sphere = 7;
	t_sphere	s[nb_sphere];
	t_list		*push;

	//Sphere(Vec3(-20,15,70),11,Color(255,255,255)),// S0
	//Sphere(Vec3(20,-15,75),13,Color(200,55,200))// S1
	s[0] = sphere_construct(vector_construct(0, 0, -10), 1.7, 0x84F15E);
	s[1] = sphere_construct(vector_construct(1e5, 0, -2500), 1e5, 0xFF0000); // RIGHT WALL
				//Sphere(Vec3(1e5,0, -2500)  ,1e5,Color(255,0,0)), //Right wall
	s[2] = sphere_construct(vector_construct(-1e5, 0, -2500), 1e5, 0x00FF00); // LEFT WALL
				//Sphere(Vec3(-1e5 ,0, -2500),1e5,Color(0,255,0)), //Left  wall
	s[3] = sphere_construct(vector_construct(0, 0, 1e5 + 100), 1e5, 0x0000FF); // BACK WALL
				//Sphere(Vec3(0,0,1e5 + 100),1e5,Color(0,0,255)),// Back wall
	s[4] = sphere_construct(vector_construct(0, 0, -1e5 - 100), 1e5, 0x005500); // FRONT WALL
				//Sphere(Vec3(0,0,-1e5 - 100),1e5,Color(0,55,0)),// Front wall
	s[5] = sphere_construct(vector_construct(0, 1e5, 2500), 1e5, 0x55F0FF); // TOP WALL
				//Sphere(Vec3(0,1e5,2500),1e5,Color(55,200,0)),// Top wall
	s[6] = sphere_construct(vector_construct(0, -1e5, -2500), 1e5, 0xFF5500); // DOWN WALL
				//Sphere(Vec3(0, -1e5, -2500),1e5,Color(200,55,0)),// Bottom wall

	while (nb_sphere-- != 0)
	{
		if (!(push = ft_lstnew(&s[nb_sphere], sizeof(t_sphere))))
			return (false);
		ft_lstadd(&e->sphere, push);
	}
	e->light.position = vector_construct(10, 10, 0);
	e->light.intensity = 1;
	e->light.color = 0xFFFFFF;
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

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(&sdl->event, &e->cam);
		update_cam(&e->cam);
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
