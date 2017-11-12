/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ellipsoid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:34:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/12 15:53:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		intersection_ellipsoid(t_ellipsoid *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = matrix_get_mult_vector(&obj->translation, &origin_object);
	origin_object = matrix_get_mult_vector(&obj->world_to_object, &origin_object);

	/*
	a = (dir_object.x*obj->size.x * dir_object.x*obj->size.x +
		 dir_object.y*obj->size.y * dir_object.y*obj->size.y +
		 dir_object.z*obj->size.z * dir_object.z*obj->size.z);
	b = (2 * origin_object.x*obj->size.x * dir_object.x*obj->size.x +
		 2 * origin_object.y*obj->size.y * dir_object.y*obj->size.y +
		 2 * origin_object.z*obj->size.z * dir_object.z*obj->size.z);
	c = (origin_object.x*obj->size.x * origin_object.x*obj->size.x +
		 origin_object.y*obj->size.y * origin_object.y*obj->size.y +
		 origin_object.z*obj->size.z * origin_object.z*obj->size.z) - obj->radius2;
	*/
	vector_scale(&origin_object, &obj->size);
	vector_scale(&dir_object, &obj->size);
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
