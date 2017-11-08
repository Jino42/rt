/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 10:09:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/08 15:23:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		intersection_plane(t_plan *obj,
								const t_vector *origin,
								const t_vector *dir,
								const float len)
{
	t_vector normal;

	t_vector	origin_object;
	//t_vector	dir_object;

	//dir_object = matrix_get_mult_dir_vector(&obj->world_to_object, dir);

	origin_object = vector_get_sub(origin, &obj->position);
	origin_object = matrix_get_mult_vector(&obj->translation, &origin_object);
	//origin_object = matrix_get_mult_vector(&obj->world_to_object, &origin_object);

	//t_vector te1 = obj->p1;
	//t_vector te2 = obj->p2;

	//te1 = matrix_get_mult_vector(&obj->world_to_object, &te1);
	//te2 = matrix_get_mult_vector(&obj->world_to_object, &te2);
	//normal = vector_get_cross_product(&te1, &te2);
	normal = vector_get_cross_product(&obj->p1, &obj->p2);
	normal = matrix_get_mult_vector(&obj->world_to_object, &normal);
	float denom = vector_dot(&normal, dir);
	if (fabs(denom) > 0.0001)
	{
		t_vector origin_to_plan = vector_get_sub(&obj->position, &origin_object);
		float t = vector_dot(&origin_to_plan, &normal) / denom;
		if (t >= 0 && t < len)
		{
			t_vector len;
			t_vector point;

			point = vector_get_mult(dir, t);
			point = vector_get_add(&point, &origin_object);
			len = vector_get_sub(&point, &obj->position);
			//disk EAsy!
			/*
				float dot = vector_magnitude(&len);
				if (sqrtf(dot) < 20)
			*/
			//SQUARE : Roatate size Wrong
			//Best way = AABB Box ?
			/*
				t_vector size = vector_construct(2, 2, 2);
				//size = vector_get_rotate_x(&size, e->temp);
				//len = vector_get_rotate_x(&len, e->temp);
				vector_abs(&len);
				vector_abs(&size);
				if (y == 240 && x == 240)
				{
					printf("Size vector : ");vector_string(&size);
					printf("Len vector  : ");vector_string(&len);
					printf("\n");
				}
				if (len.x <= size.x && len.y <= size.y && len.z <= size.z)
			*/
				return (t);
		}
	}
	return (false);
}
