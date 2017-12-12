/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:24:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:27:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		update_transform_light(const t_env *e, const t_vector *dir)
{
	t_light		*light;
	t_obj		*obj;
	uint64_t	cur;
	uint64_t	cur_light;

	cur = 0;
	cur_light = 0;
	obj = e->scene.ptr_obj + e->mem_obj_index;
	while (cur < e->mem_obj_index)
	{
		if (obj->flag & OBJ_ISLIGHT)
			cur_light += sizeof(t_light);
		cur += obj->mem_size_obj;
		obj = obj + cur;
	}
	light = e->scene.ptr_light + cur_light;
	vector_add(&light->position, dir);
}

void		update_rotation_obj(const t_env *e, const t_event *ev, t_obj *o)
{
	if (ev->key[SDL_SCANCODE_KP_1])
	{
		o->rot.x += o->rotate_speed * e->fps.delta_time;
		o->cos.x = cos(o->rot.x);
		o->sin.x = sin(o->rot.x);
	}
	if (ev->key[SDL_SCANCODE_KP_2])
	{
		o->rot.y += o->rotate_speed * e->fps.delta_time;
		o->cos.y = cos(o->rot.y);
		o->sin.y = sin(o->rot.y);
	}
	if (ev->key[SDL_SCANCODE_KP_3])
	{
		o->rot.z += o->rotate_speed * e->fps.delta_time;
		o->cos.z = cos(o->rot.z);
		o->sin.z = sin(o->rot.z);
	}
}

void		update_translate_obj(const t_env *e, const t_event *ev, t_obj *o)
{
	t_vector dir;

	if (ev->key[SDL_SCANCODE_KP_8])
		dir = vector_construct(0, 0, o->speed * e->fps.delta_time);
	if (ev->key[SDL_SCANCODE_KP_5])
		dir = vector_construct(0, 0, -o->speed * e->fps.delta_time);
	if (ev->key[SDL_SCANCODE_KP_4])
		dir = vector_construct(o->speed * e->fps.delta_time, 0, 0);
	if (ev->key[SDL_SCANCODE_KP_6])
		dir = vector_construct(-o->speed * e->fps.delta_time, 0, 0);
	if (o->flag & OBJ_ISLIGHT)
		update_transform_light(e, &dir);
	if (ev->key[SDL_SCANCODE_KP_6] || ev->key[SDL_SCANCODE_KP_4] ||
			ev->key[SDL_SCANCODE_KP_5] || ev->key[SDL_SCANCODE_KP_8])
		vector_add(&o->position, &dir);
}

void		update_scaling_obj_radius(const t_env *e, const t_event *ev,
																	t_obj *o)
{
	if (ev->key[SDL_SCANCODE_KP_7] && o->id & OBJ_SPHERE)
		((t_sphere *)o)->radius -= o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id & OBJ_SPHERE)
		((t_sphere *)o)->radius += o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_7] && o->id & OBJ_ELLIPSOID &&
										ev->key[SDL_SCANCODE_TAB])
		((t_ellipsoid *)o)->radius -= o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id & OBJ_ELLIPSOID &&
										ev->key[SDL_SCANCODE_TAB])
		((t_ellipsoid *)o)->radius += o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_7] && o->id & OBJ_CYLINDER)
		((t_cylinder *)o)->radius -= o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id & OBJ_CYLINDER)
		((t_cylinder *)o)->radius += o->speed * e->fps.delta_time;
	if (o->id == OBJ_CYLINDER)
		((t_cylinder *)o)->radius2 = ((t_cylinder *)o)->radius *
										((t_cylinder *)o)->radius;
	if (o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->radius2 = ((t_ellipsoid *)o)->radius *
										((t_ellipsoid *)o)->radius;
	if (o->id == OBJ_SPHERE)
		((t_sphere *)o)->radius2 = ((t_sphere *)o)->radius *
										((t_sphere *)o)->radius;
}

void		update_scaling_obj(const t_env *e, const t_event *ev, t_obj *o)
{
	if (ev->key[SDL_SCANCODE_KP_7] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.x += o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.y += o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_9] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.z += o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_4] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.x -= o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_5] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.y -= o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_6] && o->id == OBJ_ELLIPSOID)
		((t_ellipsoid *)o)->size.z -= o->speed * e->fps.delta_time * 0.1;
	if (ev->key[SDL_SCANCODE_KP_7] && o->id == OBJ_CONE)
		((t_cone *)o)->angle -= o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id == OBJ_CONE)
		((t_cone *)o)->angle += o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_8] && o->id == OBJ_PARABOLOID)
		((t_paraboloid *)o)->option += o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_7] && o->id == OBJ_PARABOLOID)
		((t_paraboloid *)o)->option -= o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_9] && o->id & OBJ_LIMIT)
		((t_obj_limit *)o)->limit += o->speed * e->fps.delta_time;
	if (ev->key[SDL_SCANCODE_KP_6] && o->id & OBJ_LIMIT)
		((t_obj_limit *)o)->limit -= o->speed * e->fps.delta_time;
	update_scaling_obj_radius(e, ev, o);
}
