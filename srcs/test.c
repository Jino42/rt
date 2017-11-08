#include "rt.h"

uint32_t	hex_intensity(uint32_t color, float intensity)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = (color) & 0xFF;

	r *= intensity;
	g *= intensity;
	b *= intensity;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

float 		test_light_sphere(const t_env *e, const t_light *light, const t_obj *o, const t_vector *dir, const float ret)
{
	float dot;
	t_vector dir_sphere;
	t_vector dir_sphere_to_light;
	t_vector hit;

	dot = 0;

	hit = vector_get_mult(dir, ret);
	hit = vector_get_add(&e->cam.position, &hit);

	dir_sphere = vector_get_sub(&hit, &o->position);
	dir_sphere = matrix_get_mult_vector(&o->translation, &dir_sphere);
	dir_sphere_to_light  = vector_get_sub(&light->position, &hit);

	vector_normalize(&dir_sphere);
	vector_normalize(&dir_sphere_to_light);
	dot = vector_dot(&dir_sphere, &dir_sphere_to_light);
	if (dot < 0)
		dot = 0;
	return (dot);
}

void 		*foreachpix(void *arg_thread)
{
	t_env *e;
	t_sdl *sdl;
	t_arg_thread *arg;

	arg = (t_arg_thread *)arg_thread;
	e = arg->e;
	sdl = &e->sdl;
	t_vector	dir;
	t_list		*obj;
	t_light		*light;

	light = &e->light;
	float invH = 1 / (float)sdl->height;
	float invW = 1 / (float)sdl->width;
	float ratio = sdl->width / (float)sdl->height;
	float fov = 66;
	float scale = tan(M_PI * 0.5 * fov / 180);
	float min_distance;

	float ret;

	for(uint32_t y = arg->start_y; y < arg->end_y; y++)
	{
		for(uint32_t x = 0; x < sdl->width; x++)
		{
			min_distance = INFINITY;
			float px = (2 * (((float)x + 0.5) * invW) - 1) * scale * ratio;
			float py = (1 - 2 * (((float)y + 0.5) * invH)) * scale;
			dir = vector_construct(px, py, -1);
			dir = matrix_get_mult_vector(&e->cam.camera_to_world, &dir);
			vector_normalize(&dir);
			obj = e->obj;
			while (obj)
			{
				t_obj *o = obj->content;
				ret = o->intersect(obj->content, &e->cam.position, &dir, INFINITY);
				if (ret && ret < min_distance)
				{
					if (o->id == OBJ_SPHERE)
						sdl_put_pixel(sdl, x, y, hex_intensity(o->color, test_light_sphere(e, light, o, &dir, ret)));
					else
						sdl_put_pixel(sdl, x, y, o->color);
					min_distance = ret;
				}
				obj = obj->next;
			}
		}
	}
	pthread_exit(NULL);
	return (NULL);
}
