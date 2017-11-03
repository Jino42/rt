/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/03 18:14:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include "../SDL2-2.0.5/include/SDL.h"
# include "matrix.h"

#include <sys/types.h>
#include <sys/stat.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>

# define ERROR_SDL (1 << 1)

# define HEIGHT 500
# define WIDTH 600
# define SIZE_RENDER (HEIGHT * WIDTH * 4)

# define NB_THREAD 4

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
	float			ratio;
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

typedef struct	s_cam
{
	t_vector	position;
	t_vector	angle;
	t_matrix	camera_to_world;
}				t_cam;

///////////////////////////////////////////////////

typedef struct	s_light
{
	t_vector	position;
	float		intensity;
	uint32_t	color;
}				t_light;

typedef struct 	s_sphere
{
	t_vector	position;
	float		radius;
	float		distance;
	uint32_t	color;
}				t_sphere;

typedef struct	s_plan
{
	t_vector	position;
	t_vector	p0; // Bas gauche
	t_vector	p1; // haut gauche
	t_vector	p2; // bas droite
	float		len;
	uint32_t	color;
}				t_plan;

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

	t_cam			cam;
	t_list			*sphere;
	t_list			*plan;
	t_light			light;
}					t_env;

typedef struct		s_arg_thread
{
	t_env 			*e;
	uint32_t		start_y;
	uint32_t		end_y;
}					t_arg_thread;

void 				*foreachpix(void *arg_thread);

void				update_fps(t_fps *fps);
void 				update_cam(t_cam *cam);

void 				event_cam(t_event *event, t_cam *cam);

int					end_of_program(t_env *e, char *str, int flag);
#endif
