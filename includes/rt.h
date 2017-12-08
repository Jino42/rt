/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:15:15 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/08 22:48:56 by ntoniolo         ###   ########.fr       */
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
# define F_DEBUG_SIZE_STRUCT (1 << 2)
# define F_DEBUG_PARSING (1 << 3)

# define ERROR_SDL (1 << 1)

# define HEIGHT 720
# define WIDTH 1280
# define SIZE_RENDER (HEIGHT * WIDTH * 4)

# define NB_THREAD 4


# define OBJ_SPHERE (1 << 0)
# define OBJ_PLANE (1 << 1)
# define OBJ_CYLINDER (1 << 2)
# define OBJ_PARABOLOID (1 << 3)
# define OBJ_PARABOLOID_HYPERBOLIC (1 << 4)
# define OBJ_ELLIPSOID (1 << 5)
# define OBJ_CONE (1 << 6)
# define OBJ_LIMIT (OBJ_PARABOLOID | OBJ_CYLINDER | OBJ_CONE)

# define LIGHT_BASIC (1 << 0)
# define LIGHT_SPHERE (1 << 1)
# define LIGHT_DIRECT (1 << 2)

# define F_ISLIGHT (1 << 0)


typedef struct	s_count
{
	float		time;
	uint32_t	nb_obj;
	uint32_t	nb_ray;
	uint32_t	nb_try;
	uint32_t	nb_hit;
}				t_count;

typedef struct	s_ptr_cl
{
	float		invH;
	float		invW;
	float		ratio;
	float		scale;
	float		fov;
}				t_ptr_cl;

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
	const uint32_t	*key;
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
	float		speed;
	float		speed_rotate;
}				t_cam;

///////////////////////////////////////////////////

typedef struct	s_light
{
	uint32_t		type;
	t_matrix	light_to_world;
	t_vector	position;
	float		intensity;
	uint32_t	color;
	float		radius;
	float		radius2;
	t_vector	dir;
}				t_light;

typedef struct	s_obj
{
	uint64_t	mem_size_obj;
	float		(*intersect)(void *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;
	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;
}				t_obj;
typedef struct	s_obj_limit
{
	uint64_t	mem_size_obj;
	float		(*intersect)(void *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;
	float		limit;

}				t_obj_limit;

typedef struct 	s_sphere
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_sphere *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	float		radius;
	float		radius2;
}				t_sphere;

typedef struct 	s_ellipsoid
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_ellipsoid *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	t_vector	size;
	float		radius;
	float		radius2;
}				t_ellipsoid;

typedef struct 	s_cone
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_cone *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	float		limit;

	float		angle;
}				t_cone;

typedef struct	s_paraboloid
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_paraboloid *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	float		limit;

	float		option;
}				t_paraboloid;

typedef struct	s_paraboloid_hyperbolic
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_paraboloid_hyperbolic *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	float		radius;
	float		radius2;
}				t_paraboloid_hyperbolic;

typedef struct	s_plan
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_plan *, const t_vector *,
						const t_vector *, const float);
	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	t_vector	normal;
}				t_plan;

typedef struct	s_cylinder
{
	uint64_t	mem_size_obj;
	float		(*intersect)(struct s_cylinder *, const t_vector *,
						const t_vector *, const float);

	uint32_t		id;
	uint32_t	color;
	uint32_t	flag;

	t_vector	position;
	float		rotate_speed;
	float		speed;
	t_vector	rot;
	t_vector	cos;
	t_vector	sin;
	float		m_specular;

	float		limit;

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

typedef struct	s_scene
{
	char		*name;
	t_cam		cam;

	uint64_t		mem_size_obj;
	void 			*ptr_obj;

	uint64_t		mem_size_light;
	void			*ptr_light;
}				t_scene;

typedef struct		s_env
{
	t_cl			cl;
	t_ptr_cl		p_cl;
	t_sdl			sdl;
	t_fps			fps;

	t_list			*obj;

	t_scene			scene;

	int32_t			obj_len;
	int32_t			obj_index;
	uint64_t		mem_obj_index;

	float			temp;
	int64_t			flag;

	t_count			count;
}					t_env;

typedef struct		s_arg_thread
{
	t_env 			*e;
	uint32_t		start_y;
	uint32_t		end_y;
}					t_arg_thread;

bool				flag(int64_t *f, int argc, char **argv);
bool				parse_scene(t_env *e, char *path);
void 				*foreachpix(void *arg_thread);

void				update_fps(t_fps *fps);
void 				update_cam(t_cam *cam);
void 				update_obj(t_env *e, t_sdl *sdl);

void 				event_cam(t_env *e, t_event *event, t_cam *cam);

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

int					end_of_program(t_env *e, char *str, int flag);
#endif
