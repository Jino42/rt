/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_paraboloid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:46:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/01 16:31:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		intersection_paraboloid(t_paraboloid *obj,
		const t_vector *origin,
		const t_vector *dir,
		const float len)
{
	float inter0, inter1;
	float a, b, c;
	t_vector	dir_object;
	t_vector	origin_object;

	dir_object = vector_get_rotate(dir, &obj->rot);
	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = vector_get_rotate(&origin_object, &obj->rot);

/*
**
**	Basic function
**		Can add one more parameter for grow the pointer
**		with ;
		a*=val;
		b=val*() - z
		v=val*() - z
**
*/
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
