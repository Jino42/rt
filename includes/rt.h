/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/11 21:30:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"

# include "rt_sdl.h"
# include "rt_cl.h"
# include "rt_obj.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>

# define F_DEBUG_SIZE_STRUCT (1 << 2)
# define F_DEBUG_PARSING (1 << 3)
# define F_SHADOW (1 << 15)
# define F_FOCUS (1 << 16)

# define ERROR_SDL (1 << 1)

typedef struct	s_ptr_cl
{
	float		invH;
	float		invW;
	float		ratio;
	float		scale;
	float		fov;
}				t_ptr_cl;

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
	t_cl			cl;
	t_ptr_cl		p_cl;
	t_sdl			sdl;
	t_fps			fps;

	t_scene			scene;

	int32_t			obj_index;
	uint64_t		mem_obj_index;

	int64_t			flag;
}					t_env;

bool				flag(int64_t *f, int argc, char **argv);
bool				parse_scene(t_env *e, char *path);
void				update_fps(t_fps *fps);
void 				update_cam(t_cam *cam);
void 				update_obj(t_env *e, t_sdl *sdl);
void 				event_cam(t_env *e, t_event *event, t_cam *cam);
bool				parse_scene(t_env *e, char *path);
int					end_of_program(t_env *e, char *str, int flag);

#endif
