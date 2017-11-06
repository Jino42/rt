/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_disk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 10:40:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 10:42:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		intersection_disk(t_env *e, const t_vector *dir,
										const t_vector *cam, const float len)
{
	t_plan *p = (t_plan *)e->plan->content;

	t_vector normal;
	normal = vector_get_cross_product(&p->p1, &p->p2);
	float denom = vector_dot(&normal, dir);
	if (fabs(denom) > 0.0001)
	{
		t_vector origin_to_plan = vector_get_sub(&p->position, cam);
		float t = vector_dot(&origin_to_plan, &normal) / denom;
		if (t >= 0 && t < len)
		{
			t_vector len;
			t_vector point;

			point = vector_get_mult(dir, t);
			point = vector_get_add(&point, cam);
			len = vector_get_sub(&point, &p->position);
			float dot = vector_magnitude(&len);
			if (sqrtf(dot) < p->len)
				return (t);
		}
	}
	return (false);
}
