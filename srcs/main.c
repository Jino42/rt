/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/31 16:51:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct 	s_sphere
{
	t_vector	position;
	float	radius;
}				t_sphere;

int			raytest(const t_vector *cam, const t_vector *dir, const float len)
{
	t_sphere s;

	s.position = vector_construct(10, 0, -20);
	s.radius = 1;

	t_vector originToSphere = vector_get_sub(&s.position, cam);
	float projection = vector_dot(&originToSphere, dir);
	t_vector mult = vector_get_mult(dir, projection);
	t_vector dist = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_dot(&dist, &dist);
	float radiusSq = s.radius * s.radius;
	
	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	if (newLen < len && newLen > 0)
		return (1);
	return (0);
}

int			a(t_vector orig, t_vector dir)
{
	t_sphere s;
	s.position = vector_construct(10, 1, -40);
	s.radius = 4;
	float radius2 = s.radius * s.radius;

	t_vector l = vector_get_sub(&s.position, &orig);
	float tca = vector_dot(&l, &dir);
	if (tca < 0)
		return false;
	float d2 = vector_dot(&l, &l) - tca * tca;
	if (d2 > radius2)
		return false;
	return true;
}

void 		foreachpix(t_env *e, t_sdl *sdl)
{
	t_vector dir;
	t_vector origin;

	(void)e;
	float invH = 1 / (float)sdl->height;
	float invW = 1 / (float)sdl->width;
	float ratio = sdl->width / (float)sdl->height;
	float fov = 66;
	float scale = tan(M_PI * 0.5 * fov / 180);

	for(uint32_t y=0;y<sdl->height;y++)
	{
		for(uint32_t x=0;x<sdl->width;x++)
		{
			float px = (2 * (((float)x + 0.5) * invW) - 1) * scale * ratio;
			float py = (1 - 2 * (((float)y + 0.5) * invH)) * scale;
			origin = vector_construct(0, 0, 0);
			dir = vector_construct(px, py, -1);
			//vector_sub(&dir, &origin);
			vector_normalize(&dir);
			if (raytest(&origin, &dir, 1000))
				sdl_put_pixel(sdl, x, y, 0xFF00F0);
		}
	}
	//exit(0);
}

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		foreachpix(e, sdl);
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

	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	sdl_loop(&e, &e.sdl);

	end_of_program(&e, "", 0);
	return (0);
}
