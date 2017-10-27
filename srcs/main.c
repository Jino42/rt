/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/27 22:48:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	sdl->height = HEIGHT;
	sdl->width = WIDTH;
	if (!(sdl->win = SDL_CreateWindow("rt", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, sdl->width, sdl->height,
				SDL_WINDOW_SHOWN)))
		return (0);

	if (!(sdl->render = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED)))
		return (0);
	if (!(sdl->img = SDL_CreateTexture(sdl->render,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
					sdl->width, sdl->height)))
		return (0);
	if (!(sdl->pix = ft_memalloc(sizeof(uint32_t) * sdl->width * sdl->height)))
		return (0);
	return (1);
}           ///////////// Can be resize ?

void		sdl_update_event(t_sdl *sdl, t_event *event)
{
	(void)event;
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

bool		sdl_event_exit(t_sdl *sdl)
{
	return (sdl->event.exit);
}
//////////////https://openclassrooms.com/courses/developpez-vos-applications-3d-avec-opengl-3-3/les-evenements-avec-la-sdl-2-0https://openclassrooms.com/courses/developpez-vos-applications-3d-avec-opengl-3-3/les-evenements-avec-la-sdl-2-0
void		sdl_loop(t_env *e, t_sdl *sdl)
{
	while (!sdl_event_exit(sdl))
	{
		update_fps(&e->fps);
		sdl_update_event(sdl, &sdl->event);
		for(int y=0;y<100;y++)
			for(int x=0;x<100;x++)
				sdl->pix[x + y * sdl->width] = 0xFF0000;
		SDL_UpdateTexture(sdl->img, NULL, sdl->pix, sdl->width * sizeof(uint32_t));
		SDL_RenderCopy(sdl->render, sdl->img, NULL, NULL);
		SDL_RenderPresent(sdl->render);
		SDL_RenderClear(sdl->render);
	}
}

int main(int argc, char **argv)
{
	(void)argc;(void)argv;

	t_env e;

	ft_bzero(&e, sizeof(t_env));

	if (!sdl_init(&e.sdl))
		return (end_of_program(&e, "Erreur a l'initialisation", ERROR_SDL));
	sdl_loop(&e, &e.sdl);

	end_of_program(&e, "", 0);
	return (0);
}
