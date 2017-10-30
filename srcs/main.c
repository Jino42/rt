/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/30 00:05:19 by ntoniolo         ###   ########.fr       */
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

	s.position = vector_construct(0, 0, -5);
	s.radius = 1;

	t_vector originToSphere = vector_get_sub(&s.position, cam);
	float projection = vector_dot(&originToSphere, dir);
	t_vector mult = vector_get_mult(dir, projection);
	t_vector dist = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_dot(&dist, &dist);
	float radiusSq = s.radius * s.radius;

	//rintf("%.2f %.2f\n", distanceSq, radiusSq);
	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	//printf("%.2f > %.2f\n", newLen, len);
	if (newLen < len && newLen > 0)
		return (1);
	return (0);
}


bool solveQuadratic(const float a, const float b, const float c, float x0, float x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0)
		return false;
    else if (discr == 0)
        x0 = x1 = - 0.5 * b / a;
    else
	{
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }

    return true;
}


int			a(t_vector orig, t_vector dir)
{
	t_sphere s;

	s.position = vector_construct(0, 0, -20);
	s.radius = 4;

	float t0, t1;
	(void)orig;
	float radius2 = s.radius * s.radius;

	t_vector l = vector_get_sub(&s.position, &orig);
	float tca = vector_dot(&l, &dir);
	if (tca < 0)
		return false;
	float d2 = vector_dot(&l, &l) - tca * tca;
	//printf("D2 %.2f, radius %.2f\n", d2, radius2);
	if (d2 > radius2)
		return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}

bool 		b(t_sdl *sdl, t_vector oo, t_vector dd)
{
	t_sphere s;

	s.position = vector_construct(sdl->width * 0.5, sdl->height * 0.5, 50);
	s.radius = 50;

	t_vector o = oo;
    t_vector d = dd;
    t_vector oc = vector_get_sub(&o, &s.position);
    float b = 2 * vector_dot(&oc, &d);
    float c = vector_dot(&oc, &oc) - s.radius * s.radius;
    float disc = b*b - 4 * c;
    if (disc < 1e-4)
		return false;
    disc = sqrt(disc);
    float t0 = -b - disc;
    float t1 = -b + disc;
	float t;
    t = (t0 < t1) ? t0 : t1;
	return true;
}

float deg2rad(const float deg)
{ return deg * M_PI / 180; }

void 		foreachpix(t_env *e, t_sdl *sdl)
{
	t_vector dir;
	t_vector origin;

	float invH = 1 / (float)sdl->height;
	float invW = 1 / (float)sdl->width;
	float ratio = sdl->width / (float)sdl->height;
	float scale = tan(M_PI * 0.5 * 66 / 180);
	printf("W %.4f | H %.4f | R %.4f | S %4f\n", invW, invH, ratio, scale);
	(void)e;
	for(uint32_t y=0;y<sdl->height;y++)
	{
		for(uint32_t x=0;x<sdl->width;x++)
		{
			float px = (2 * (((float)x + 0.5) * invW) - 1) * scale * ratio;
			float py = (1 - 2 * (((float)y + 0.5) * invH)) * scale;
			origin = vector_construct(0, 0, 0);
			dir = vector_construct(px, py, -1);
			//vector_sub(&dir, &origin);
			if (x == 270  && y == 140)
				printf(" x %f y %f z %f\n", dir.x, dir.y, dir.z);
			vector_normalize(&dir);
			if (a(origin, dir))
			{
				sdl_put_pixel(sdl, x, y, 0xFF00F0);
			}
		}
	}
	//exit(0);
}

void 		new(t_env *e, t_sdl *sdl)
{
	(void)e;
	for (uint32_t y = 0; y < sdl->height; ++y)
	{
		for (uint32_t x = 0; x < sdl->width; ++x)
		{
			t_vector origin = vector_construct(0, 0, 1);
			t_vector dir = vector_construct(x, y, 0);
			if (b(sdl, dir, origin)) /////////
				sdl_put_pixel(sdl, x, y, 0xFF00F0);
		}
	}
}

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		for(int y=0;y<100;y++)
			for(int x=0;x<100;x++)
				sdl_put_pixel(sdl, x, y, 0xFF00F0);
		foreachpix(e, sdl);
		//new (e, sdl);
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
