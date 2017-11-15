#include "matrix.hl"
#include "local_function.hl"
#include "rt.hl"

#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#pragma OPENCL EXTENSION cl_khr_fp16 : enable

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
								const float len,
								int nb, int x, int y)
{
	float inter0, inter1;
	float a, b, c;

	t_vector	origin_object;
	t_vector	dir_object;
/*
	if (nb == 0 && !x && !y)
	{
			printf("%i : %.2f %.2f %.2f\n", nb,
				   	obj->position.x,
				   	obj->position.y,
				   	obj->position.z);
			printf("Size de l'objet : %i\n", obj->mem_size_obj);
			printf("Id   de l'objet : %i\n", obj->id);
			printf("Colorde l'objet : %x\n", obj->color);
			printf("Radius -> %.2f\n", obj->radius);
	}
*/
	dir_object = local_matrix_get_mult_dir_vector(&obj->world_to_object, dir);
//	dir_object = *dir;

/*
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
	o.speed +=0.01;
*/


	origin_object = local_vector_get_sub(origin, &obj->position);
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

__kernel void test(__global int *img,
					__global char *objj,
					unsigned long mem_size_obj,
					t_ptr_cl	p_cl,
					t_cam		cam,
					__local char *lobj)
{

	__global t_obj *o;
	__local	char testt[2000];
	__local t_obj *q;	

	int w = 1280;
	int x = get_global_id(0) % w;
	int y = get_global_id(0) / w;
	int grp = get_group_id(0);
	int a = y;
	int num_elems = get_local_size(0);
	event_t ev;
//	event_t ev = async_work_group_copy(test, objj + grp * num_elems, num_elems, 0);

	ev = async_work_group_copy(testt, objj, mem_size_obj, 0);
	wait_group_events(1, &ev);
	/*

	// Wait for copies to complete
	if (x == 0 && y == 0)
	while (x + a * w < (int)mem_size_obj)
	{
		event_t ev = async_work_group_copy(test,
					test + x + a * w, 1, 0);
		wait_group_events(1, &ev);
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
	int i = 0;
	__local t_sphere *m;
	while (i < 8)
	{
		o = (__global t_obj *)(objj + sizeof(t_sphere) * i);
		//test = (lobj + sizeof(t_sphere) * i);
		q = (__local t_obj *)(testt + sizeof(t_sphere) * i);
		m= (__local t_sphere *)(testt+sizeof(t_sphere) * i);	
/*	if (i == 0  && x == 0 && y == 0)
		{
			printf("OBJJ  %i : %.2f %.2f %.2f\n", i,
				   	o->position.x,
				   	o->position.y,
				   	o->position.z);
			printf("TESTT %i : %.2f %.2f %.2f\n", i,
				   	q->position.x,
				   	q->position.y,
				   	q->position.z);
		}*/
		if ((ret = intersection_sphere(m, &cam.position, &dir, INFINITY, i, x, y)) &&
												ret < min_distance)
		{
			img[x + y * w]  = o->color;
			min_distance = ret;
		}
		i++;
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
