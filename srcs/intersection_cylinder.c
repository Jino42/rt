/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/07 18:58:47 by ntoniolo         ###   ########.fr       */
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
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;


	dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);
	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = matrix_get_mult_vector(&obj->world_to_object, &origin_object);
	a = dir_object.x * dir_object.x + dir_object.z * dir_object.z;
	b = 2 * origin_object.x * dir_object.x +
		2 * origin_object.z * dir_object.z;
	c = origin_object.x * origin_object.x +
		origin_object.z * origin_object.z - obj->radius2;
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
/*
Cylinder :
x^2 + z^2 - r^2 = 0
|O + Dt| = p;
(p.x + p.z)^2 − R^2 = 0


*/
