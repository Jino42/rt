#include "matrix.hl"
#include "rt.hl"


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


float		intersection_sphere(t_sphere *obj,
								const t_vector *origin,
								const t_vector *dir,
								const float len)
{
	float inter0, inter1;
	float a, b, c;

	t_sphere o = *obj;

	t_vector	origin_object;
	t_vector	dir_object;

//	dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);
	dir_object = *dir;

/*
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
*/

	
	origin_object = vector_get_sub(origin, &obj->position);
//	origin_object = matrix_get_mult_vector(&obj->translation, &origin_object);
//	origin_object = matrix_get_mult_vector(&obj->world_to_object, &origin_object);


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

__kernel void test(__global int *img,
					__global char *objj,
					unsigned long long mem_size_obj,
					t_ptr_cl	p_cl,
					t_cam		cam,
					__local char *lobj)
{

	__global t_obj *o;
	__local	t_obj *test;

	int w = 1280;
	int x = get_global_id(0) % w;
	int y = get_global_id(0) / w;
	int grp = get_group_id(0);
	int a = y;
	/*
	if (x == 0 && y == 0)
	while (x + a * w < (int)mem_size_obj)
	{
		lobj[x + a * w] = objj[x + a * w];
		a++;
	}
	*/
	t_vector dir;
	float min_distance = INFINITY;
	float ret;
	float px = (2 * (((float)x + 0.5) * p_cl.invW) - 1) * p_cl.scale * p_cl.ratio;
	float py = (1 - 2 * (((float)y + 0.5) * p_cl.invH)) * p_cl.scale;

	dir = vector_construct(px, py, -1);
	dir = matrix_get_mult_vector(&cam.camera_to_world, &dir);
	vector_normalize(&dir);
	for (int i = 0; i < 8; i++)
	{
		o = (__global t_obj *)(objj + sizeof(t_sphere) * i);
		test = (lobj + sizeof(t_sphere) * i);
/*
		if (x == 20 &&  y == 2)
			printf("%.2f %.2f %.2f\n",
				   	test->position.x,
				   	test->position.y,
				   	test->position.z);
*/
		if ((ret = intersection_sphere(o, &cam.position, &dir, INFINITY)) &&
												ret < min_distance)
		{
			img[x + y * w]  = o->color;
			min_distance = ret;
		}
	}
/*
	if (x == 0 && y == 0)
	{
		__global t_obj *o = (__global t_obj *)(objj + sizeof(t_sphere));
		t_vector v = o->position;
		printf("Vector position id : %i : %.2f %.2f %.2f\n",
			   o->id,
			   v.x, v.y, v.z);
		int i = 0;
		printf("Mem_obj : \n");
		printf("\nMem img : \n");
		i = 0;
		while (i++ < 20)
			printf("[%x]", img[i + 1280 * 700]);
		printf("\n%llu\n", mem_size_obj);
	}
	img[x + y * w] = 0xFF00FF;
*/
}
