/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/13 18:29:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libft/includes/libft.h"
# include "../vector/includes/vector.h"
# include "../SDL2-2.0.5/include/SDL.h"
# include "matrix.h"
# include "rt_cl.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>

# define F_CPU (1 << 1)

# define ERROR_SDL (1 << 1)

# define HEIGHT 720
# define WIDTH 1280
# define SIZE_RENDER (HEIGHT * WIDTH * 4)

# define NB_THREAD 1

# define OBJ_SPHERE 0
# define OBJ_PLANE 1
# define OBJ_CYLINDER 2
# define OBJ_PARABOLOID 3
# define OBJ_PARABOLOID_HYPERBOLIC 4
# define OBJ_ELLIPSOID 5
# define OBJ_CONE 6

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
	t_matrix	light_to_world;
	t_vector	position;
	float		intensity;
	uint32_t	color;
}				t_light;

typedef struct	s_obj
{
	float		(*intersect)(void *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;
	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;
}				t_obj;

typedef struct 	s_sphere
{
	float		(*intersect)(struct s_sphere *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;

	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	float		radius;
	float		radius2;
}				t_sphere;

typedef struct 	s_ellipsoid
{
	float		(*intersect)(struct s_ellipsoid *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;

	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	t_vector	size;
	float		radius;
	float		radius2;
}				t_ellipsoid;

typedef struct 	s_cone
{
	float		(*intersect)(struct s_cone *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;

	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	float		radius;
	float		radius2;
}				t_cone;

typedef struct	s_paraboloid
{
	float		(*intersect)(struct s_paraboloid *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;
	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	float		radius;
	float		radius2;
}				t_paraboloid;

typedef struct	s_paraboloid_hyperbolic
{
	float		(*intersect)(struct s_paraboloid_hyperbolic *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;
	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	float		radius;
	float		radius2;
}				t_paraboloid_hyperbolic;

typedef struct	s_plan
{
	float		(*intersect)(struct s_plan *, const t_vector *,
						const t_vector *, const float);
	uint8_t		id;
	uint32_t	color;
	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	t_vector	p0; // Bas gauche
	t_vector	p1; // haut gauche RELATIVE
	t_vector	p2; // bas droite RELATIVE
	float		len;
}				t_plan;

typedef struct	s_cylinder
{
	float		(*intersect)(struct s_cylinder *, const t_vector *,
						const t_vector *, const float);

	uint8_t		id;
	uint32_t	color;
	t_vector	position;
	t_matrix	world_to_object;
	t_matrix	translation;
	float		rotate_speed;
	float		speed;

	t_vector	hit_point;
	t_vector	hit_normal;

	float		radius;
	float		radius2;
}				t_cylinder;

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
	t_cl			cl;
	t_sdl			sdl;
	t_fps			fps;

	t_cam			cam;
	t_list			*sphere;
	t_list			*plan;
	t_list			*cylinder;
	t_light			light;

	t_list			*obj;
	int32_t		obj_len;
	int32_t		obj_index;

	float			temp;
	int64_t			flag;
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
void 				update_obj(t_env *e, t_sdl *sdl);

void 				event_cam(t_event *event, t_cam *cam);

bool				solve_quadratic(const float a, const float b, const float c,
							float *inter0, float *inter1);

float				intersection_sphere(t_sphere *obj, const t_vector *origin, const t_vector *dir,
							const float len);
float				geo_intersection_sphere(const t_vector *origin, const t_vector *dir,
							const float len, t_sphere *s);
float				intersection_plane(t_plan *obj, const t_vector *origin,
							const t_vector *dir, const float len);
float				intersection_cylinder(t_cylinder *obj, const t_vector *origin, const t_vector *dir,
							const float len);
float				intersection_paraboloid(t_paraboloid *obj, const t_vector *origin, const t_vector *dir,
							const float len);
float				intersection_paraboloid_hyperbolic(t_paraboloid_hyperbolic *obj, const t_vector *origin, const t_vector *dir,
							const float len);
float				intersection_ellipsoid(t_ellipsoid *obj, const t_vector *origin, const t_vector *dir,
							const float len);
float				intersection_cone(t_cone *obj, const t_vector *origin, const t_vector *dir,
							const float len);

float				intersection_disk(t_env *e, const t_vector *dir,
							const t_vector *cam, const float len);
int					end_of_program(t_env *e, char *str, int flag);
#endif
