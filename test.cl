#include "matrix.hl"
#include "local_function.hl"
#include "rt.hl"

bool		solve_quadratic(const float a, const float b, const float c,
								float *inter0, float *inter1);
float		intersection_sphere(__local t_sphere *obj, const t_vector *origin,
								const t_vector *dir, const float len);
float		intersection_ellipsoid(__local t_ellipsoid *obj, const t_vector *origin,
								const t_vector *dir, const float len);

bool		solve_quadratic(const float a, const float b, const float c,
								float *inter0, float *inter1)
{
	float discr;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr < 0.000005)
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


float		intersection_sphere(__local t_sphere *obj,
								const t_vector *origin,
								const t_vector *dir,
								const float len)
{
	float inter0, inter1;
	float a, b, c;

	t_vector	origin_object;
	t_vector	dir_object;

	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = local_matrix_get_mult_vector(&obj->world_to_object, &origin_object);


	a = 1; //Donc 1
	b = 2 * vector_dot(&dir_object, &origin_object);
	c = vector_magnitude(&origin_object) - obj->radius2;
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

float		intersection_ellipsoid(__local t_ellipsoid *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = local_matrix_get_mult_vector(&obj->world_to_object, &origin_object);

	local_vector_scale(&origin_object, &obj->size);
	local_vector_scale(&dir_object, &obj->size);
	a = (dir_object.x * dir_object.x +
	 	 dir_object.y * dir_object.y +
	 	 dir_object.z * dir_object.z);
	 b = (2 * origin_object.x * dir_object.x +
		  2 * origin_object.y * dir_object.y +
		  2 * origin_object.z * dir_object.z);
	 c = (origin_object.x * origin_object.x +
		  origin_object.y * origin_object.y +
		  origin_object.z * origin_object.z) - obj->radius2;
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

float		intersection_cylinder(__local t_cylinder *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len,
									t_ray_ret *r)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;
	t_vector y_axis = vector_construct(0, -1, 0);
/*
	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);
	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = local_matrix_get_mult_vector(&obj->world_to_object, &origin_object);
*/
	dir_object = vector_get_rotate_local(dir, &obj->rot);
	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = vector_get_rotate_local(&origin_object, &obj->rot);

	a = dir_object.x * dir_object.x + dir_object.z * dir_object.z;
	b = 2 * origin_object.x * dir_object.x +
		2 * origin_object.z * dir_object.z;
	c = origin_object.x * origin_object.x +
		origin_object.z * origin_object.z - obj->radius2;
	if (!solve_quadratic(a, b, c, &inter0, &inter1))
		return (0);
	if (inter0 > inter1)
	{
		y_axis = vector_construct(0, 1, 0);
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
	{
		/*
		r->hit_point = vector_get_mult(dir, inter0);
		r->hit_point = vector_get_add(origin, &r->hit_point);

//		r->hit_point.y = obj->position.y; // Normal Cylinder

		r->hit_normal = vector_get_sub_local(&r->hit_point, &obj->position);
		r->hit_normal = local_matrix_get_mult_vector(&obj->translation, &r->hit_normal);
		r->hit_normal = local_matrix_get_mult_vector(&obj->world_to_object, &r->hit_normal);
		t_matrix z = obj->world_to_object;
		z.matrix[1][1] = -z.matrix[1][1];
		z.matrix[1][2] = -z.matrix[1][2];
		z.matrix[2][2] = -z.matrix[2][2];
		z.matrix[2][1] = -z.matrix[2][1];
		r->hit_point.y = obj->position.y; // Normal Cylinder
		r->hit_normal = matrix_get_mult_vector(&z, &r->hit_normal);

		//r->hit_normal = local_matrix_get_mult_vector(&obj->world_to_object, &r->hit_normal);
		vector_normalize(&r->hit_normal);
		*/
/********
		t_vector y_axis = vector_construct(0, 1, 0);

		y_axis = local_matrix_get_mult_vector(&obj->world_to_object, &y_axis);

		r->hit_point = vector_get_mult(dir, inter0);
		r->hit_point = vector_get_add(origin, &r->hit_point);

		t_vector tee = vector_get_sub_local(origin, &obj->position);
		float res = vector_dot(&dir_object, &y_axis) * inter0 + vector_dot(&origin_object, &y_axis);
		t_vector ta = vector_get_mult(&y_axis, res);
		r->hit_normal = vector_get_sub_local(&r->hit_point, &obj->position);
		r->hit_normal = vector_get_sub(&r->hit_normal, &ta);

		vector_normalize(&r->hit_normal);
*/
/*
		t_vector y_axis = vector_construct(0, 1, 0);

		y_axis = local_matrix_get_mult_vector(&obj->world_to_object, &y_axis);

		r->hit_point = vector_get_mult(dir, inter0);
		r->hit_point = vector_get_add(origin, &r->hit_point);

		t_vector tmp = vector_get_sub(&r->hit_point, origin);
		float len = vector_magnitude(&tmp);
		float m = vector_dot(&dir_object, &y_axis) * len; //
		tmp = vector_get_sub_local(origin, &obj->position); //
		m += vector_dot(&tmp, &y_axis);
		tmp = vector_get_sub_local(&r->hit_point, &obj->position);
		r->hit_normal = vector_get_mult(&y_axis, m);
		r->hit_normal = vector_get_sub(&tmp, &r->hit_normal);
		vector_normalize(&r->hit_normal);
*/

		//t_vector y_axis = vector_construct(0, 1, 0);

		/////y_axis = vector_get_rotate_local(&y_axis, &obj->rot);
		//y_axis = local_matrix_get_mult_vector(&obj->world_to_object, &y_axis);

		r->hit_point = vector_get_mult(dir, inter0);
		r->hit_point = vector_get_add(origin, &r->hit_point);

		t_vector poshit = vector_get_sub_local(&r->hit_point, &obj->position);
		poshit = vector_get_rotate_local(&poshit, &obj->rot);

		//t_vector osef = local_vector_get_sub(&obj->position, origin);
		//m = vec3_dot(r->dir, obj->dir) * o->in + vec3_dot(r->pos, obj->dir);

		float m = vector_dot(&dir_object, &y_axis) * inter0  + vector_dot(&origin_object, &y_axis);
		r->hit_normal = vector_get_mult(&y_axis, m);
		r->hit_normal = vector_get_sub(&poshit, &r->hit_normal);

		r->hit_normal = vector_get_inverse_rotate_local(&r->hit_normal, &obj->rot);
		vector_normalize(&r->hit_normal);

		return (inter0);
	}
	return (0);
}

float		intersection_cone(__local t_cone *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = local_matrix_get_mult_vector(&obj->world_to_object, &origin_object);

	a = (dir_object.x * dir_object.x +
	 	 dir_object.y * dir_object.y -
	 	 dir_object.z * dir_object.z);
	 b = (2 * origin_object.x * dir_object.x +
		  2 * origin_object.y * dir_object.y -
		  2 * origin_object.z * dir_object.z);
	 c = (origin_object.x * origin_object.x +
		  origin_object.y * origin_object.y -
		  origin_object.z * origin_object.z);
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

float		intersection_paraboloid(__local t_paraboloid *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = local_matrix_get_mult_vector(&obj->world_to_object, &origin_object);

	a = (dir_object.x * dir_object.x + dir_object.z * dir_object.z);
	b = (2 * origin_object.x * dir_object.x +
		2 * origin_object.z * dir_object.z) - (dir_object.y);
	c = (origin_object.x * origin_object.x +
		origin_object.z * origin_object.z) - (origin_object.y);
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

float		intersection_plane(__local t_plan *obj,
								const t_vector *origin,
								const t_vector *dir,
								const float len)
{
	t_vector normal;

	t_vector	origin_object;

	origin_object = vector_get_sub_local(origin, &obj->position);
	origin_object = local_matrix_get_mult_vector(&obj->translation, &origin_object);


	normal = local_vector_get_cross_product_local(&obj->p1, &obj->p2); //
	normal = local_matrix_get_mult_vector(&obj->world_to_object, &normal);
	float denom = vector_dot(&normal, dir);
	if (fabs(denom) > 0.0001)
	{
		t_vector origin_to_plan = local_vector_get_sub(&obj->position, &origin_object); //
		float t = vector_dot(&origin_to_plan, &normal) / denom;
		if (t >= 0 && t < len)
		{
			t_vector len;
			t_vector point;

			point = vector_get_mult(dir, t);
			point = vector_get_add(&point, &origin_object);
			len = vector_get_sub_local(&point, &obj->position);
			return (t);
		}
	}
	return (false);
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

__kernel void test(__global int *img,
					__global char *g_mem_obj,
					unsigned long mem_size_obj,
					t_ptr_cl	p_cl,
					t_cam		cam,
					__local char *l_mem_obj)
{

	__local t_obj		*o;

	int x = get_global_id(0) % WIDTH;
	int y = get_global_id(0) / WIDTH;
	event_t ev;

	ev = async_work_group_copy(l_mem_obj, g_mem_obj, mem_size_obj, 0);
//	barrier(CLK_LOCAL_MEM_FENCE);
	wait_group_events(1, &ev);

	t_vector dir;
	float min_distance = INFINITY;
	float ret;
	float px = (2 * (((float)x + 0.5) * p_cl.invW) - 1) * p_cl.scale * p_cl.ratio;
	float py = (1 - 2 * (((float)y + 0.5) * p_cl.invH)) * p_cl.scale;

	dir = vector_construct(px, py, -1);
	dir = matrix_get_mult_vector(&cam.camera_to_world, &dir);
	vector_normalize(&dir);
	int i = 0;
	unsigned long cur = 0;

	while (cur < mem_size_obj)
	{
		t_ray_ret tmp_r;
		ret = 0;
		o = (__local t_obj *)(l_mem_obj + cur);
		if (o->id == OBJ_SPHERE)
		{
			ret = intersection_sphere((__local t_sphere *)o, &cam.position, &dir, INFINITY);
			cur += sizeof(t_sphere);
		}
		else if (o->id == OBJ_ELLIPSOID)
		{
			ret = intersection_ellipsoid((__local t_ellipsoid *)o, &cam.position, &dir, INFINITY);
			cur += sizeof(t_ellipsoid);
		}
		else if (o->id == OBJ_CONE)
		{
			ret = intersection_cone((__local t_cone *)o, &cam.position, &dir, INFINITY);
			cur += sizeof(t_cone);
		}
		else if (o->id == OBJ_CYLINDER)
		{
			t_vector y_axis = vector_construct(0, 1, 0);

			//y_axis = local_matrix_get_mult_vector(&o->world_to_object, &y_axis);
			y_axis = vector_get_rotate_local(&y_axis, &o->rot);
		//	if (!x && !y)
			//	printf("Dir Cylinder : %.2f %.2f %.2f\n", o->rot.x, o->rot.y, o->rot.z);
			ret = intersection_cylinder((__local t_cylinder *)o, &cam.position, &dir, INFINITY, &tmp_r);
			cur += sizeof(t_cylinder);
		}
		else if (o->id == OBJ_PARABOLOID)
		{
			ret = intersection_paraboloid((__local t_paraboloid *)o, &cam.position, &dir, INFINITY);
			cur += sizeof(t_paraboloid);
		}
		else if (o->id == OBJ_PLANE)
		{
			ret = intersection_plane((__local t_plan *)o, &cam.position, &dir, INFINITY);
			cur += sizeof(t_plan);
		}
/*
		if (i == 0  && x == 0 && y == 0)
		{
			printf("OBJJ  %i : %.2f %.2f %.2f\n", i,
				   	o->position.x,
				   	o->position.y,
				   	o->position.z);
			printf("TESTT %i : %.2f %.2f %.2f\n", i,
				   	q->position.x,
				   	q->position.y,
				   	q->position.z);
		}
*/

		if (ret && ret < min_distance)
		{
			if (o->id == OBJ_SPHERE)
			{
				t_vector	hit_point;
				t_vector	hit_normal;
				float		ret_dot;
				t_vector place_light = vector_construct(10, 10, 0);
				t_vector dir_obj_to_light;

				hit_point = vector_get_mult(&dir, ret);
				hit_point = vector_get_add(&cam.position, &hit_point);

				hit_normal = vector_get_sub_local(&hit_point, &o->position);
				vector_normalize(&hit_normal);

				dir_obj_to_light = vector_get_sub(&place_light, &hit_point);
				vector_normalize(&dir_obj_to_light);

				ret_dot = vector_dot(&hit_normal, &dir_obj_to_light);
				if (ret_dot < 0)
					ret_dot = 0;

				img[x + y * WIDTH]  = hex_intensity(o->color, ret_dot);
			}
			else if (o->id == OBJ_CYLINDER)
			{
				float		ret_dot;
				t_vector place_light = vector_construct(10, 10, 0);
				t_vector dir_obj_to_light;

				//Vec3f V = (E - P).normalize(); // or -ray.dir if you use ray-tracing

				dir_obj_to_light = vector_get_sub(&place_light, &tmp_r.hit_point);
				vector_normalize(&dir_obj_to_light);

				ret_dot = vector_dot(&tmp_r.hit_normal, &dir_obj_to_light);
				if (ret_dot < 0)
					ret_dot = 0;

				img[x + y * WIDTH]  = hex_intensity(o->color, ret_dot);
			}
			else if (o->id == OBJ_PLANE)
			{
				float		ret_dot;
				t_vector place_light = vector_construct(10, 10, 0);
				t_vector dir_obj_to_light;

				//Vec3f V = (E - P).normalize(); // or -ray.dir if you use ray-tracing

				t_vector hh = vector_get_mult(&dir, ret);
				hh = vector_get_add(&cam.position, &hh);
				dir_obj_to_light = vector_get_sub(&place_light, &hh);
				vector_normalize(&dir_obj_to_light);
				__local t_plan *pp = ((__local t_plan *)o);
				t_vector normal = local_vector_get_cross_product_local(&pp->p1, &pp->p2);
				normal = local_matrix_get_mult_vector(&pp->world_to_object, &normal);
				ret_dot = vector_dot(&normal, &dir_obj_to_light);
				if (ret_dot < 0)
					ret_dot = -ret_dot;

				img[x + y * WIDTH]  = hex_intensity(o->color, ret_dot);
			}
			else
				img[x + y * WIDTH] = o->color;
			min_distance = ret;
		}
		i++;
	}
}
