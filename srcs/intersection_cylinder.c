/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/17 15:01:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		intersection_cylinder(t_cylinder *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	//dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);
	dir_object = vector_get_rotate(dir, &obj->rot);
	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = vector_get_rotate(&origin_object, &obj->rot);
	//origin_object = matrix_get_mult_vector(&obj->translation, &origin_object);
	//origin_object = matrix_get_mult_vector(&obj->world_to_object, &origin_object);
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
