#include "rt.h"
/*
int			raytest(const t_vector *cam, const t_vector *dir, const float len)
{
	t_sphere s;

	s.position = vector_construct(0, 0, -10);
	s.radius = 1.7;
	t_vector originToSphere = vector_get_sub(&s.position, cam);
	float projection = vector_dot(&originToSphere, dir);
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
*/
float			raytest(const t_vector *cam, const t_vector *dir, const float len, t_sphere *s)
{
	t_vector originToSphere = vector_get_sub(&s->position, cam);
	float projection = vector_dot(&originToSphere, dir);
	/*get exatly closest point to sphere center*/
	t_vector mult = vector_get_mult(dir, projection);
	t_vector sphere_to_intersect = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_magnitude(&sphere_to_intersect);
	float radiusSq = s->radius * s->radius;

	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	if (newLen < len && newLen > 0)
	{
		//s->distance = newLen;
		return (newLen);
	}
	return (0);
}

bool		sphere_quadratic(const float a, const float b, const float c,
							float *inter0, float *inter1)
{
	float discr;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr < 0.000005)
	{
		*inter0 = -0.5 * b / a; ///////////>
		*inter1 = *inter0;
	}
	else
	{
		float q = (b > 0) ? (-0.5 * (b + sqrt(discr))): (-0.5 * (b - sqrt(discr)));
		*inter0 = q / a;
		*inter1 = c / q;
	}
	if (*inter0 > *inter1)
	{
		float tmp;

		tmp = *inter0;
		*inter0 = *inter1;
		*inter1 = tmp;
	}
	return (true);
}

float		intersect(const t_vector *cam, const t_vector *dir, const float len, t_sphere *s)
{
	float inter0, inter1; //Point d'intersection
	float a, b, c;
	t_vector	originToSphere;

	originToSphere = vector_get_sub(cam, &s->position); ///////////>
	a = 1; //Donc 1
	b = 2 * vector_dot(dir, &originToSphere); ///////////>
	c = vector_magnitude(&originToSphere) - s->radius * s->radius;
	if (!sphere_quadratic(a, b, c, &inter0, &inter1))
		return (0);
	if (inter0 > inter1)
	{
		float tmp = inter0;
		inter0 = inter1;
		inter1 = tmp;
	}
	if (inter0 < 0)
	{
		inter0 = inter1;
		if (inter0 < 0)
			return (0);
	}
	if (inter0 < len)
		return (inter0);
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
	//t_list		*list_light;
	t_sphere	*s;
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
			obj = e->sphere;
			while (obj)
			{
				s = (t_sphere *)obj->content;
				//ret = raytest(&e->cam.position, &dir, INFINITY, s);
				ret = intersect(&e->cam.position, &dir, INFINITY, s);
				if (ret)
				{
					if (ret < min_distance)
					{
						float dot = 0;
						t_vector hit;
						hit = vector_get_mult(&dir, ret);
						hit = vector_get_add(&e->cam.position, &hit);
						t_vector dir_sphere = vector_get_sub(&hit, &s->position);
						//list_light = e->light;
						//while (list_light)
						//{
						//	light = (t_light*)list_light->content;
							t_vector dir_sphere_to_light  = vector_get_sub(&light->position, &hit);
							vector_normalize(&dir_sphere);
							vector_normalize(&dir_sphere_to_light);
							dot = vector_dot(&dir_sphere, &dir_sphere_to_light);
							if (dot < 0)
								dot = 0;
						//	list_light = list_light->next;
						//}
							sdl_put_pixel(sdl, x, y, hex_intensity(s->color, dot));

						//sdl_put_pixel(sdl, x, y, s->color);
						min_distance = ret;
					}
				}
				obj = obj->next;
			}
		}
	}
	pthread_exit(NULL);
	return (NULL);
	//exit(0);
}
