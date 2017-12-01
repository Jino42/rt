/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 09:59:42 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/01 16:31:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			geo_intersection_sphere(const t_vector *origin, const t_vector *dir,
													const float len, t_sphere *s)
{
	t_vector originToSphere = vector_get_sub(&s->position, origin);
	float projection = vector_dot(&originToSphere, dir);
	/*get exatly closest point to sphere center*/
	t_vector mult = vector_get_mult(dir, projection);
	t_vector sphere_to_intersect = vector_get_sub(&originToSphere, &mult);
	float distanceSq = vector_magnitude(&sphere_to_intersect);
	float radiusSq = s->radius * s->radius;

	if (distanceSq > radiusSq)
		return (0);
	float newLen = projection - sqrt(radiusSq - distanceSq);
	if (newLen < len && newLen > 0)
	{
		//s->distance = newLen;
		return (newLen);
	}
	return (0);
}

float		intersection_sphere(t_sphere *obj,
									const t_vector *origin,
									const t_vector *dir,
									const float len)
{
	float inter0, inter1;
	float a, b, c;

	t_vector	origin_object;
	t_vector	dir_object;

	dir_object = vector_get_rotate(dir, &obj->rot);
	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = vector_get_rotate(&origin_object, &obj->rot);


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

/*
**
**	Geometric reduce function. Need to learn it
	int			intersection_sphere(t_vector orig, t_vector dir)
	{
		t_sphere s;

		s.position = vector_construct(10, 1, -40);
		s.radius = 4;
		float radius2 = s.radius * s.radius;

		t_vector l = vector_get_sub(&s.position, &orig);
		float tca = vector_dot(&l, &dir);
		if (tca < 0)
			return false;
		float d2 = vector_dot(&l, &l) - tca * tca;
		if (d2 > radius2)
			return false;
		return true;
	}
*/
