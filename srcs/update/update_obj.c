/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:05:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 22:27:31 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		update_obj_index(t_env *e, const int32_t incr)
{
	t_obj			*o;
	static time_t	save = 0;

	if (save == e->fps.cur.tv_sec)
		return ;
	o = (t_obj *)(e->scene.ptr_obj + e->mem_obj_index);
	if (o->flag & OBJ_ISFOCUS)
		o->flag ^= OBJ_ISFOCUS;
	save = e->fps.cur.tv_sec;
	if (incr > 0)
		e->mem_obj_index +=
				((t_obj *)(e->scene.ptr_obj + e->mem_obj_index))->mem_size_obj;
	if (e->mem_obj_index == e->scene.mem_size_obj)
		e->mem_obj_index = 0;
	o = (t_obj *)(e->scene.ptr_obj + e->mem_obj_index);
	ft_printf("%i/%i\n TYPE %i\n", e->mem_obj_index, e->scene.mem_size_obj,
					((t_obj *)(e->scene.ptr_obj + e->mem_obj_index))->id);
	if (o->flag & OBJ_ISFOCUS)
		o->flag ^= OBJ_ISFOCUS;
}

void			update_obj(t_env *e, t_sdl *sdl)
{
	t_event		*ev;
	t_obj		*o;

	ev = &sdl->event;
	if (ev->key[SDL_SCANCODE_KP_PLUS])
		update_obj_index(e, 1);
	if (ev->key[SDL_SCANCODE_KP_MINUS])
		update_obj_index(e, -1);
	o = (t_obj *)(e->scene.ptr_obj + e->mem_obj_index);
	update_rotation_obj(e, ev, o);
	if (ev->key[SDL_SCANCODE_LSHIFT])
		update_translate_obj(e, ev, o);
	if (!ev->key[SDL_SCANCODE_LSHIFT])
		update_scaling_obj(e, ev, o);
	if (ev->key[SDL_SCANCODE_TAB])
		e->flag & F_SHADOW ? (e->flag ^= F_SHADOW) : 0;
	else
		e->flag |= F_SHADOW;
	if (ev->key[SDL_SCANCODE_F])
		e->flag |= F_FOCUS;
	else
		e->flag & F_FOCUS ? (e->flag ^= F_FOCUS) : 0;
}
