/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:43:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 18:41:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parse.h"

static void		parse_rotation_obj(t_obj *o, const t_vector *rot)
{
	o->rot.x = rot->x;
	o->cos.x = cos(o->rot.x);
	o->sin.x = sin(o->rot.x);
	o->rot.y = rot->y;
	o->cos.y = cos(o->rot.y);
	o->sin.y = sin(o->rot.y);
	o->rot.z = rot->z;
	o->cos.z = cos(o->rot.z);
	o->sin.z = sin(o->rot.z);
}

static void		parse_translate_obj(t_obj *o, const t_vector *dir)
{
	vector_add(&o->position, dir);
}

static void		parse_scaling_obj(t_obj *o, const float scaling)
{
	if (o->id & OBJ_SPHERE)
	{
		((t_sphere *)o)->radius *= scaling;
		((t_sphere *)o)->radius2 = pow(((t_sphere *)o)->radius, 2);
	}
	else if (o->id & OBJ_ELLIPSOID)
	{
		((t_ellipsoid *)o)->radius *= scaling;
		((t_ellipsoid *)o)->radius2 = pow(((t_ellipsoid *)o)->radius, 2);
	}
	else if (o->id & OBJ_CYLINDER)
	{
		((t_cylinder *)o)->radius *= scaling;
		((t_cylinder *)o)->radius2 = pow(((t_cylinder *)o)->radius, 2);
	}
	else if (o->id == OBJ_CONE)
		((t_cone *)o)->angle *= scaling;
	else if (o->id == OBJ_PARABOLOID)
		((t_paraboloid *)o)->option *= scaling;
}

/*
** Translate
** Rotation
** Scaling
*/

bool			parse_transform(t_scene *scene, char *line_fd)
{
	t_vector	translate;
	t_vector	rotation;
	float		scaling;
	t_obj		*obj;

	translate = vector_construct(0, 0, 0);
	rotation = vector_construct(0, 0, 0);
	scaling = 0;

	if (!is_encaps(line_fd, 3))
		return (false);
	if (!get_vec(strchr_arg(line_fd, 1), &translate))
		return (false);
	if (!get_vec(strchr_arg(line_fd, 2), &rotation))
		return (false);
	if (!get_float(strchr_arg(line_fd, 3), &scaling))
		return (false);
	if (!(obj = parse_get_last_obj(scene)))
		return (false);
	parse_translate_obj(obj, &translate);
	parse_rotation_obj(obj, &rotation);
	parse_scaling_obj(obj, scaling);
	return (true);
}
