/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:32:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/27 21:52:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	end_sdl(t_sdl *sdl)
{
	SDL_Quit();
	if (sdl->pix)
		ft_memdel((void **)&sdl->pix);
	if (sdl->img)
		SDL_DestroyTexture(sdl->img);
	if (sdl->render)
		SDL_DestroyRenderer(sdl->render);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
}

int		end_of_program(t_env *e, char *str, int flag)
{
	if (str)
		ft_dprintf(2, "%s\n", str);
	if (flag)
		ft_dprintf(2, "%s\n", SDL_GetError());
	end_sdl(&e->sdl);
	return (0);
}
