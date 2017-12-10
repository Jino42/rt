/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:32:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 18:43:14 by ntoniolo         ###   ########.fr       */
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

void 	free_list_object(void *ptr, size_t size_content)
{
	(void)size_content;
	(void)ptr;
}

int		end_of_program(t_env *e, char *str, int flag)
{
	if (str)
		ft_dprintf(2, "%s\n", str);
	if (flag)
		ft_dprintf(2, "%s\n", SDL_GetError());
	cl_end(&e->cl);
	end_sdl(&e->sdl);
	return (0);
}
