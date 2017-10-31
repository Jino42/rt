/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/01 00:02:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct 	s_sphere
{
	t_vector	position;
	float	radius;
}				t_sphere;

typedef struct	s_pxtopx
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
}				t_pxtopx;

int			raytest(const t_vector *cam, const t_vector *dir, const float len)
{
	t_sphere s;

	s.position = vector_construct(0, 0, -10);
	s.radius = 1.7;
	t_vector originToSphere = vector_get_sub(&s.position, cam);
	float projection = vector_dot(&originToSphere, dir);
	/*get exatly closest point to sphere center*/
	t_vector mult = vector_get_mult(dir, projection);
	t_vector sphere_to_intersect = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_magnitude(&sphere_to_intersect);
	float radiusSq = s.radius;

	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	if (newLen < len && newLen > 0)
		return (1);
	return (0);
}

int			raytest_test(const t_vector *cam, const t_vector *dir, const float len, const t_sphere s)
{
	t_vector originToSphere = vector_get_sub(&s.position, cam);
	float projection = vector_dot(&originToSphere, dir);
	/*get exatly closest point to sphere center*/
	t_vector mult = vector_get_mult(dir, projection);
	t_vector sphere_to_intersect = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_magnitude(&sphere_to_intersect);
	float radiusSq = s.radius * s.radius;

	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	if (newLen < len && newLen > 0)
		return (1);
	return (0);
}

void test(t_env *e, t_sdl *sdl, t_vector dir, const uint32_t x, const uint32_t y)
{
	t_sphere s;

	s.position = vector_construct(1e5, 0, -2500);
	s.radius = 1e5;
	if (raytest_test(&e->cam.position, &dir, 1000, s))
		sdl_put_pixel(sdl, x, y, 0xF47710);
	s.position = vector_construct(0, 1e5, -2500);
	s.radius = 1e5;
	if (raytest_test(&e->cam.position, &dir, 1000, s))
		sdl_put_pixel(sdl, x, y, 0x55FF00);
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
			dir = vector_construct(px, py, -1);
			dir = matrix_get_mult_vector(&e->cam.camera_to_world, &dir);
			vector_normalize(&dir);
			if (raytest(&e->cam.position, &dir, 1000))
			//if (a(e->cam.position, dir)) // 25 -> 29/30 FPS
				sdl_put_pixel(sdl, x, y, 0xFF00F0);
			test(e, sdl, dir, x, y);
		}
	}
	//exit(0);
}

void 		update_camera(t_cam *cam)
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

void 		event_cam(t_event *event, t_cam *cam)
{
	t_vector	dir;

	float speed = 0.07;
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

void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		event_cam(&sdl->event, &e->cam);
		update_camera(&e->cam);
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
