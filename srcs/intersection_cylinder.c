/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 23:34:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
Vector3d rayD = ray.get_dir();
Vector3d cylD = cyl->get_dir();
Vector3d deltaP = ray.get_orig() - cyl->center();
double a =     (rayD-(cylD*(rayD*cylD)))*(rayD-(cylD*(rayD*cylD)));
double b = 2*( (rayD-(cylD*(rayD*cylD)))*(deltaP-(cylD*(deltaP*cylD))) );
double c = (deltaP-(cylD*(deltaP*cylD)))*(deltaP-(cylD*(deltaP*cylD))) - cyl->get_r()*cyl->get_r();
double disc	= b * b - 4.0 * a * c;
*/

float		intersection_cylinder(const t_vector *origin, const t_vector *dir,
										const float len, t_cylinder *obj, t_env *e)
{
	(void)e;
	float inter0, inter1; //Point d'intersection
	float a, b, c;
	t_vector	origin_object;
	t_vector	dir_object;
	t_vector	origin_to_cylinder;


	origin_object = matrix_get_mult_vector(&obj->world_to_object, origin);
	dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);
	//t_vector t = vector_construct(-10, -10, -10);
	//t_matrix trans = matrix_get_translation(&t);
	//t_matrix rot = matrix_get_rotation_x(e->temp);
	//t_matrix final = matrix_get_mult_matrix(&rot, &trans);
	//t_vector new_o = matrix_get_mult_vector(&final, origin);
	origin_to_cylinder = vector_get_sub(&origin_object, &obj->position); ///////////>
	//t_vector new;
	//new = matrix_get_mult_vector(&final, dir);
	//new = matrix_get_mult_dir_vector(&final, dir);
	//(p - pa + vt - (va,p - pa + vt)va)2 - r2
	//(xE + t * Dx)^2 + (yE + t * Dy)^2 - 1 = 0
	a = dir_object.x * dir_object.x + dir_object.z * dir_object.z;
	b = 2 * origin_to_cylinder.x * dir_object.x +
		2 * origin_to_cylinder.z * dir_object.z;
	c = origin_to_cylinder.x * origin_to_cylinder.x +
		origin_to_cylinder.z * origin_to_cylinder.z - obj->radius2;
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
	{
		t_vector point;

		point = vector_get_mult(&dir_object, inter0);
		//if (fabs(point.y) < 4)
			return (inter0);
	}
	return (0);
}
/*
Cylinder :
x^2 + z^2 - r^2 = 0
|O + Dt| = p;
(p.x + p.z)^2 − R^2 = 0


*/
