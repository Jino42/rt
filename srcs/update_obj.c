/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:05:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/08 14:38:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list		*ft_lst_index(t_list *l, uint32_t index)
{
	while (l)
	{
		if (!index)
			return (l);
		l = l->next;
		index--;
	}
	return (NULL);
}

static void 	update_transform_obj(const t_env *e, const t_event *ev, t_obj *o)
{
	t_vector dir;

	if (ev->key[SDL_SCANCODE_KP_1])
		matrix_rotation_x(&o->world_to_object, o->rotate_speed * e->fps.delta_time);
	if (ev->key[SDL_SCANCODE_KP_2])
		matrix_rotation_y(&o->world_to_object, o->rotate_speed * e->fps.delta_time);
	if (ev->key[SDL_SCANCODE_KP_3])
		matrix_rotation_z(&o->world_to_object, o->rotate_speed * e->fps.delta_time);
	if (ev->key[SDL_SCANCODE_KP_8])
	{
		dir = vector_construct(0, 0, o->speed * e->fps.delta_time);
		matrix_translation(&o->translation, &dir);
	}
	if (ev->key[SDL_SCANCODE_KP_5])
	{
		dir = vector_construct(0, 0, -o->speed * e->fps.delta_time);
		matrix_translation(&o->translation, &dir);
	}
	if (ev->key[SDL_SCANCODE_KP_4])
	{
		dir = vector_construct(o->speed * e->fps.delta_time, 0, 0);
		matrix_translation(&o->translation, &dir);
	}
	if (ev->key[SDL_SCANCODE_KP_6])
	{
		dir = vector_construct(-o->speed * e->fps.delta_time, 0, 0);
		matrix_translation(&o->translation, &dir);
	}
}

void 		update_obj_index(t_env *e, const int32_t incr)
{
	t_obj	*o;

	e->obj_index += incr;
	if (e->obj_index < 0)
		e->obj_index = e->obj_len - 1;
	if (e->obj_index == e->obj_len)
		e->obj_index = 0;
	o = (t_obj *)(ft_lst_index(e->obj, e->obj_index)->content);
	ft_printf("%i/%i\n TYPE %i\n", e->obj_index, e->obj_len, o->id);
}

void 		update_obj(t_env *e, t_sdl *sdl)
{
	t_obj		*o;
	t_event		*ev;

	ev = &sdl->event;
	if (ev->key[SDL_SCANCODE_KP_PLUS])
		update_obj_index(e, 1);
	if (ev->key[SDL_SCANCODE_KP_MINUS])
		update_obj_index(e, -1);

	o = (t_obj *)(ft_lst_index(e->obj, e->obj_index)->content);

	update_transform_obj(e, ev, o);
}
