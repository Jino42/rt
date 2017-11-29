#include "matrix.hl"
#include "local_function.hl"
#include "rt.hl"

bool		solve_quadratic(const float a, const float b, const float c,
								float *inter0, float *inter1);
float		intersection_sphere(const __local t_sphere *obj, const t_vector *origin_object,
								const t_vector *dir_object, const float len);
float		intersection_ellipsoid(const __local t_ellipsoid *obj, t_vector *origin,
								t_vector *dir, const float len, t_ray_ret *r);
float		intersection_planeconst (__local t_plan *obj, const t_vector *origin,
								const t_vector *dir, const float len);
float		intersection_ellipsoid(const __local t_ellipsoid *obj, t_vector *origin_object,
								t_vector *dir_object, const float len, t_ray_ret *r);
float		intersection_cylinder(const __local t_cylinder *obj, const t_vector *origin_object,
								const t_vector *dir_object, const float len, t_ray_ret *r);
float		intersection_paraboloid(const __local t_paraboloid *obj, const t_vector *origin_object,
								const t_vector *dir_object, const float len, t_ray_ret *r);
float		calculate_m_value(t_ray_ret *r, const t_vector *origin_object, const t_vector *dir_object, float inter0, float inter1);

void	normal_ellipsoid(__local t_ellipsoid *obj, t_ray_ret *r);
void	normal_cylinder(__local t_cylinder *obj, t_ray_ret *r);
void	normal_paraboloid(__local t_paraboloid *obj, t_ray_ret *r);
void	normal_sphere(__local t_sphere *obj, t_ray_ret *r);
void	normal_plan(__local t_plan *obj, t_ray_ret *r);

unsigned int	hex_intensity(unsigned int color, float intensity);

t_ray_ret		ray_intersection(__local char *l_mem_obj, unsigned long mem_size_obj, t_vector *dir, t_vector *origin, __global t_count *count);
t_ray_ret		ray_intersection2(__local char *l_mem_obj, unsigned long mem_size_obj, t_vector *dir, t_vector *origin);

/*|
**|
**|
*/

bool		solve_quadratic(const float a, const float b, const float c,
								float *inter0, float *inter1)
{
	float discr;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr < EPSILON)
	{
		*inter0 = -0.5 * b / a;
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

float		intersection_sphere(const __local t_sphere *obj,
								const t_vector *origin_object,
								const t_vector *dir_object,
								const float len)
{
	float inter0, inter1;
	float a, b, c;


	a = 1;
	b = 2 * vector_dot(dir_object, origin_object);
	c = vector_magnitude(origin_object) - obj->radius2;
	if (!solve_quadratic(a, b, c, &inter0, &inter1))
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

float		intersection_plane(const __local t_plan *obj,
								const t_vector *origin,
								const t_vector *dir,
								const float len)
{
	t_vector normal;

	t_vector	origin_object;

	origin_object = vector_get_sub_local(origin, &obj->position);

	normal = obj->normal;
	normal = vector_get_inverse_rotate_local(&normal, &obj->rot);

	float denom = vector_dot(&normal, dir);
	if (fabs(denom) > EPSILON)
	{
		t_vector origin_to_plan = local_vector_get_sub(&obj->position, &origin_object); //
		float t = vector_dot(&origin_to_plan, &normal) / denom;
		if (t >= 0 && t < len)
			return (t);
	}
	return (false);
}

float		intersection_ellipsoid(const __local t_ellipsoid *obj,
									t_vector *origin_object,
									t_vector *dir_object,
									const float len,
									t_ray_ret *r)
{
	float inter0, inter1;
	float a, b, c;


	vector_div_vector_local(origin_object, &obj->size);
	vector_div_vector_local(dir_object, &obj->size);

	a = (dir_object->x * dir_object->x +
	 	 dir_object->y * dir_object->y +
	 	 dir_object->z * dir_object->z);
	 b = (2 * origin_object->x * dir_object->x +
		  2 * origin_object->y * dir_object->y +
		  2 * origin_object->z * dir_object->z);
	 c = (origin_object->x * origin_object->x +
		  origin_object->y * origin_object->y +
		  origin_object->z * origin_object->z) - obj->radius2;
	if (!solve_quadratic(a, b, c, &inter0, &inter1))
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

float		calculate_m_value(t_ray_ret *r, const t_vector *origin_object, const t_vector *dir_object, float inter0, float inter1)
{
	r->m = vector_dot(dir_object, &r->y_axis) * inter0  + vector_dot(origin_object, &r->y_axis);
	if (r->m > 10 || r->m < -10)
	{
		r->m = vector_dot(dir_object, &r->y_axis) * inter1 + vector_dot(origin_object, &r->y_axis);
		if (r->m > 10 || r->m < -10)
			return (0);
		return (inter1);
	}
	return (inter0);
}

float		intersection_cylinder(const __local t_cylinder *obj,
									const t_vector *origin_object,
									const t_vector *dir_object,
									const float len,
									t_ray_ret *r)
{
	float inter0, inter1;
	float a, b, c;

	a = dir_object->x * dir_object->x + dir_object->z * dir_object->z;
	b = 2 * origin_object->x * dir_object->x +
		2 * origin_object->z * dir_object->z;
	c = origin_object->x * origin_object->x +
		origin_object->z * origin_object->z - obj->radius2;
	if (!solve_quadratic(a, b, c, &inter0, &inter1))
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
		return (calculate_m_value(r, origin_object, dir_object, inter0, inter1));
	return (0);
}

float		intersection_paraboloid(const __local t_paraboloid *obj,
									const t_vector *origin_object,
									const t_vector *dir_object,
									const float len,
									t_ray_ret *r)
{
	float inter0, inter1;
	float a, b, c;

	a = (dir_object->x * dir_object->x + dir_object->z * dir_object->z);
	b = (2 * origin_object->x * dir_object->x +
		2 * origin_object->z * dir_object->z) - (dir_object->y);
	c = (origin_object->x * origin_object->x +
		origin_object->z * origin_object->z) - (origin_object->y);
	if (!solve_quadratic(a, b, c, &inter0, &inter1))
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
		return (calculate_m_value(r, origin_object, dir_object, inter0, inter1));
	return (0);
}

void	normal_ellipsoid(__local t_ellipsoid *obj, t_ray_ret *r)
{
	r->hit_normal.x = r->position_obj_to_hit.x / (obj->size.x * obj->size.x);
	r->hit_normal.y = r->position_obj_to_hit.y / (obj->size.y * obj->size.y);
	r->hit_normal.z = r->position_obj_to_hit.z / (obj->size.z * obj->size.z);
}
void	normal_cylinder(__local t_cylinder *obj, t_ray_ret *r)
{
	r->hit_normal = vector_get_mult(&r->y_axis, r->m);
	r->hit_normal = vector_get_sub(&r->position_obj_to_hit, &r->hit_normal);
}
void	normal_paraboloid(__local t_paraboloid *obj, t_ray_ret *r)
{
	r->hit_normal = vector_get_mult(&r->y_axis, r->m);
	r->hit_normal = vector_get_sub(&r->position_obj_to_hit, &r->hit_normal);
}
void	normal_sphere(__local t_sphere *obj, t_ray_ret *r)
{
	r->hit_normal = r->position_obj_to_hit;
}
void	normal_plan(__local t_plan *obj, t_ray_ret *r)
{
	r->hit_normal = obj->normal;
}

unsigned int	hex_intensity(unsigned int color, float intensity)
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

t_ray_ret		ray_intersection(__local char *l_mem_obj,
								unsigned long mem_size_obj,
								t_vector *dir,
								t_vector *origin,
								__global t_count *count)
{
	t_ray_ret			tmp_r;
	t_ray_ret			ray_ret;

	__local t_obj		*obj;
	unsigned long		cur;

	float				min_distance;

	t_vector			dir_object;
	t_vector			origin_object;

	tmp_r.y_axis = vector_construct(0, 1, 0);
	min_distance = INFINITY;
	cur = 0;
	while (cur < mem_size_obj)
	{
		atomic_inc(&count->nb_try);
		tmp_r.distance_intersection = 0;
		obj = (__local t_obj *)(l_mem_obj + cur);

		dir_object = vector_get_rotate_local(dir, &obj->rot);
		origin_object = vector_get_sub_local(origin, &obj->position);
		origin_object = vector_get_rotate_local(&origin_object, &obj->rot);

		if (obj->id == OBJ_SPHERE)
		{
			tmp_r.distance_intersection = intersection_sphere((__local t_sphere *)obj, &origin_object, &dir_object, INFINITY);
			cur += sizeof(t_sphere);
		}
		else if (obj->id == OBJ_PLANE)
		{
			tmp_r.distance_intersection = intersection_plane((__local t_plan *)obj, origin, dir, INFINITY);
			cur += sizeof(t_plan);
		}
		else if (obj->id == OBJ_ELLIPSOID)
		{
			tmp_r.distance_intersection = intersection_ellipsoid((__local t_ellipsoid *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_ellipsoid);
		}
		else if (obj->id == OBJ_CONE)
		{
			cur += sizeof(t_cone);
		}
		else if (obj->id == OBJ_PARABOLOID)
		{
			tmp_r.distance_intersection = intersection_paraboloid((__local t_paraboloid *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_paraboloid);
		}
		else if (obj->id == OBJ_CYLINDER)
		{
			tmp_r.distance_intersection = intersection_cylinder((__local t_cylinder *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_cylinder);
		}

		if (fabs(tmp_r.distance_intersection) > EPSILON &&
				tmp_r.distance_intersection < min_distance)
		{
			atomic_inc(&count->nb_hit);
			tmp_r.ptr_obj = obj;
			min_distance = tmp_r.distance_intersection;
			ray_ret = tmp_r;
		}
	}
	return (ray_ret);
}
t_ray_ret		ray_intersection2(__local char *l_mem_obj,
								unsigned long mem_size_obj,
								t_vector *dir,
								t_vector *origin)
{
	t_ray_ret			tmp_r;
	t_ray_ret			ray_ret;

	__local t_obj		*obj;
	unsigned long		cur;

	float				min_distance;

	t_vector			dir_object;
	t_vector			origin_object;

	tmp_r.y_axis = vector_construct(0, 1, 0);
	min_distance = INFINITY;
	cur = 0;
	while (cur < mem_size_obj)
	{
		obj = (__local t_obj *)(l_mem_obj + cur);
		tmp_r.distance_intersection = 0;

		dir_object = vector_get_rotate_local(dir, &obj->rot);
		origin_object = vector_get_sub_local(origin, &obj->position);
		//origin_object = vector_get_rotate_local(&origin_object, &obj->rot);
		t_vector taa2t = vector_construct(obj->rot.x, obj->rot.y, obj->rot.z);
		origin_object = vector_get_rotate(&origin_object, &taa2t);

		if (obj->id == OBJ_SPHERE)
		{
			tmp_r.distance_intersection = intersection_sphere((const __local t_sphere *)obj, &origin_object, &dir_object, INFINITY);
			cur += sizeof(t_sphere);
		}
		else if (obj->id == OBJ_PLANE)
		{
			tmp_r.distance_intersection = intersection_plane((const __local t_plan *)obj, origin, dir, INFINITY);
			cur += sizeof(t_plan);
		}
		else if (obj->id == OBJ_ELLIPSOID)
		{
			tmp_r.distance_intersection = intersection_ellipsoid((const __local t_ellipsoid *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_ellipsoid);
		}
		else if (obj->id == OBJ_CONE)
		{
			cur += sizeof(t_cone);
		}
		else if (obj->id == OBJ_PARABOLOID)
		{
			tmp_r.distance_intersection = intersection_paraboloid((const __local t_paraboloid *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_paraboloid);
		}
		else if (obj->id == OBJ_CYLINDER)
		{
			tmp_r.distance_intersection = intersection_cylinder((const __local t_cylinder *)obj, &origin_object, &dir_object, INFINITY, &tmp_r);
			cur += sizeof(t_cylinder);
		}

		if (fabs(tmp_r.distance_intersection) > EPSILON &&
				tmp_r.distance_intersection < min_distance)
		{
			tmp_r.ptr_obj = obj;
			min_distance = tmp_r.distance_intersection;
			ray_ret = tmp_r;
		}
		//cur += obj->mem_size_obj;
	}
	return (ray_ret);
}

__kernel void test(__global int *img,
					__global char *g_mem_obj,
					unsigned long mem_size_obj,
					t_ptr_cl	p_cl,
					t_cam		cam,
					__local char *l_mem_obj,
					__global char *g_mem_light,
					unsigned long mem_size_light,
					__local char *l_mem_light,
					__global t_count *count)
{

	__local t_obj		*o;

	int x = get_global_id(0) % WIDTH;
	int y = get_global_id(0) / WIDTH;
	event_t ev;

	ev = async_work_group_copy(l_mem_obj, g_mem_obj, mem_size_obj, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy(l_mem_light, g_mem_light, mem_size_light, 0);
	wait_group_events(1, &ev);

	t_vector dir;
	float px = (2 * (((float)x + 0.5) * p_cl.invW) - 1) * p_cl.scale * p_cl.ratio;
	float py = (1 - 2 * (((float)y + 0.5) * p_cl.invH)) * p_cl.scale;

	dir = vector_construct(px, py, -1);
	dir = matrix_get_mult_vector(&cam.camera_to_world, &dir);
	vector_normalize(&dir);

	t_ray_ret ray_ret = ray_intersection(l_mem_obj, mem_size_obj, &dir, &cam.position, count);

	//AFTER
	o = ray_ret.ptr_obj;
	ray_ret.hit_point = vector_get_mult(&dir, ray_ret.distance_intersection);
	ray_ret.hit_point = vector_get_add(&cam.position, &ray_ret.hit_point);

	//LIGHT
	__local t_light *light = (__local t_light *)l_mem_light;
	t_vector dir_obj_to_light;
	t_vector dir_light_to_obj;

	dir_obj_to_light = local_vector_get_sub(&light->position, &ray_ret.hit_point);
	dir_light_to_obj = vector_get_sub_local(&ray_ret.hit_point, &light->position);
	vector_normalize(&dir_obj_to_light);
	vector_normalize(&dir_light_to_obj);

	//SHAD

	t_vector light_position = light->position;
//	t_ray_ret ray_shad = ray_intersection2(l_mem_obj, mem_size_obj, &dir_light_to_obj, &light_position);
	float aza = 1;
//	if (ray_shad.ptr_obj != ray_ret.ptr_obj)
//		aza = 0;

	ray_ret.position_obj_to_hit = vector_get_sub_local(&ray_ret.hit_point, &o->position);
	ray_ret.position_obj_to_hit = vector_get_rotate_local(&ray_ret.position_obj_to_hit, &o->rot);

	if (o->id == OBJ_SPHERE)
		normal_sphere((__local t_sphere *)o, &ray_ret);
	else if (o->id == OBJ_PARABOLOID)
		normal_paraboloid((__local t_paraboloid *)o, &ray_ret);
	else if (o->id == OBJ_ELLIPSOID)
		normal_ellipsoid((__local t_ellipsoid *)o, &ray_ret);
	else if (o->id == OBJ_PLANE)
		normal_plan((__local t_plan *)o, &ray_ret);
	else if (o->id == OBJ_CYLINDER)
		normal_cylinder((__local t_cylinder *)o, &ray_ret);

	ray_ret.hit_normal = vector_get_inverse_rotate_local(&ray_ret.hit_normal, &o->rot);
	vector_normalize(&ray_ret.hit_normal);

	float		ret_dot;


	ret_dot = vector_dot(&ray_ret.hit_normal, &dir_obj_to_light);
	if (o->id == OBJ_PLANE && ret_dot < 0)
		ret_dot = fabs(ret_dot);
	else if (ret_dot < 0)
		ret_dot = 0;
	img[x + y * WIDTH]  = hex_intensity(o->color, ret_dot * aza);
}
