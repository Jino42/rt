/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/04 23:32:45 by ntoniolo         ###   ########.fr       */
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

t_plan		plan_construct(const t_vector position, const float len,
							const uint32_t color)
{
	t_plan p;

	p.color = color;
	p.position = position;
	p.len = len;

	p.p0 = vector_construct(position.x - len, position.y - len, position.z);
	p.p1 = vector_construct(0, len * 2, 0);
	p.p1 = vector_get_add(&p.p0, &p.p1);
	p.p2 = vector_construct(len * 2, 0, 0);
	p.p2 = vector_get_add(&p.p0, &p.p2);
	printf("Position = %.2f %.2f %.2f\n", p.position.x, p.position.y, p.position.z);
	printf("P0 = %.2f %.2f %.2f\n", p.p0.x, p.p0.y, p.p0.z);
	printf("P1 = %.2f %.2f %.2f\n", p.p1.x, p.p1.y, p.p1.z);
	printf("P2 = %.2f %.2f %.2f\n", p.p2.x, p.p2.y, p.p2.z);
	return (p);
}

bool 		init_object(t_env *e)
{
	uint32_t	nb_sphere = 7;
	t_sphere	s[nb_sphere];
	t_list		*push;

	//Sphere(Vec3(-20,15,70),11,Color(255,255,255)),// S0
	//Sphere(Vec3(20,-15,75),13,Color(200,55,200))// S1
	s[0] = sphere_construct(vector_construct(10, 10, -10), 1.7, 0x84F15E);
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

	t_plan p;

	p = plan_construct(vector_construct(0, 0, -10), 1, 0xFF00FF);
	if (!(push = ft_lstnew(&p, sizeof(t_plan))))
		return (false);
	ft_lstadd(&e->plan, push);
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
	t_event *ev;

	ev = &sdl->event;
	if (ev->key[SDL_SCANCODE_T])
	{
		e->temp += 0.04;
	}

	if (ev->key[SDL_SCANCODE_Y])
		vector_rotate_y(&((t_plan *)e->plan->content)->p2, 0.04);
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
