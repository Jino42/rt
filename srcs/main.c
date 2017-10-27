/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/27 20:19:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SDL2-2.0.5/include/SDL.h"
#include "unistd.h"

#include "rt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	ft_printf("Slt\n");
	t_vector a;
	a.x = 2;
	vector_abs(&a);
	(void)argc;(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Quit();
		return (0);
	}
	SDL_Window *fenetre;

	fenetre = SDL_CreateWindow("Slt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);


	SDL_Event event;
	int end = 0;
	while (!end)
	{
		SDL_WaitEvent(&event);
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			end = 1;
	}

	SDL_DestroyWindow(fenetre);
	write(1, "End\n", 4);
	SDL_Quit();
	return (0);
}
