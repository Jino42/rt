/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:32:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/11 23:15:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	end_sdl(t_sdl *sdl)
{
	if (sdl->pix)
		ft_memdel((void *)&sdl->pix);
	if (sdl->img)
		SDL_DestroyTexture(sdl->img);
	if (sdl->render)
		SDL_DestroyRenderer(sdl->render);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	env_end(t_env *e)
{
	if (e->scene.ptr_obj)
		ft_memdel(&e->scene.ptr_obj);
	if (e->scene.ptr_light)
		ft_memdel(&e->scene.ptr_light);
	if (e->scene.name)
		ft_memdel((void *)&e->scene.name);
}

int		end_of_program(t_env *e, char *str, int flag)
{
	if (str)
		ft_dprintf(2, "%s\n", str);
	if (flag)
		ft_dprintf(2, "%s\n", SDL_GetError());
	env_end(e);
	cl_end(&e->cl);
	end_sdl(&e->sdl);
	return (0);
}
