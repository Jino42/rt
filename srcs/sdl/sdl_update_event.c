/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_update_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:37:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/29 15:40:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_update_event(t_sdl *sdl, t_event *event)
{
	while (SDL_PollEvent(&sdl->ev))
	{
		if (sdl->ev.type == SDL_KEYDOWN)
			event->key[sdl->ev.key.keysym.scancode] = true;
		else if (sdl->ev.type == SDL_KEYUP)
			event->key[sdl->ev.key.keysym.scancode] = false;
		else if (sdl->ev.type == SDL_MOUSEMOTION)
		{
			event->m_x = sdl->ev.motion.x;
			event->m_y = sdl->ev.motion.y;
		}
		else if (sdl->ev.type == SDL_MOUSEBUTTONDOWN)
			event->mouse[sdl->ev.button.button] = true;
		else if (sdl->ev.type == SDL_MOUSEBUTTONUP)
			event->mouse[sdl->ev.button.button] = false;
		if (sdl->ev.type == SDL_WINDOWEVENT)
		{
			if (sdl->ev.window.event == SDL_WINDOWEVENT_CLOSE)
				event->exit = true;
		}
	}
	if (event->key[SDL_SCANCODE_ESCAPE])
		event->exit = true;
}
