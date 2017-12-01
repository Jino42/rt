/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_paraboloid_hyperbolic.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:26:28 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/01 16:31:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
DOS NOT WORKK !!!!
*/

float		intersection_paraboloid_hyperbolic(t_paraboloid_hyperbolic *obj,
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
	float temp;

	temp = 1;
	a = temp * (dir_object.x * dir_object.x - dir_object.z * dir_object.z);
	b = temp * (2 * origin_object.x * dir_object.x -
		2 * origin_object.z * dir_object.z) - (dir_object.y);
	c = temp * (origin_object.x * origin_object.x -
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
