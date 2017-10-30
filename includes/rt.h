/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/29 23:57:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include "../SDL2-2.0.5/include/SDL.h"

#include <sys/types.h>
#include <sys/stat.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

# define ERROR_SDL (1 << 1)

# define HEIGHT 720
# define WIDTH 1080
# define SIZE_RENDER (HEIGHT * WIDTH * 4)

///////////////////////////////////////////////////

typedef struct		s_event
{
	bool			key[SDL_NUM_SCANCODES]; //////double key pour only press ?
	bool			mouse[8];

	int				m_x;
	int				m_y;
	bool			exit;
}					t_event;

typedef struct		s_sdl
{
	uint32_t		width;
	uint32_t		height;
	float		ratio;
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Texture		*img;
	SDL_Event		ev;
	t_event			event;
	const uint8_t	*key;
	uint32_t		*pix;
}					t_sdl;

bool				sdl_init(t_sdl *sdl);
void 				sdl_put_pixel(t_sdl *sdl, const uint32_t x,
						const uint32_t y, uint32_t const col);
void 				sdl_update_event(t_sdl *sdl, t_event *event);
bool				sdl_event_exit(t_sdl *sdl);
bool				sdl_key(t_sdl *sdl, const uint32_t key);

//Do class ?
///////////////////////////////////////////////////

typedef struct		s_fps
{
	struct timeval	step2;
	struct timeval	step;
	struct timeval	cur;
	float			delta_time;
	unsigned int	fps;
	unsigned int	ret_fps;
}					t_fps;

typedef struct		s_env
{
	t_sdl			sdl;
	t_fps			fps;
}					t_env;

void				update_fps(t_fps *fps);

int					end_of_program(t_env *e, char *str, int flag);
#endif
