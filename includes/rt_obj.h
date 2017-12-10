
#ifndef RT_OBJ_H
# define RT_OBJ_H

# include "vector.h"
# include "matrix.h"

# define NB_OBJ 7

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

typedef struct	s_cam
{
	t_vector	position;
	t_vector	angle;
	t_matrix	camera_to_world;
	float		speed;
	float		speed_rotate;
}				t_cam;

typedef struct	s_scene
{
	char		*name;
	t_cam		cam;

	uint64_t		mem_size_obj;
	void 			*ptr_obj;

	uint64_t		mem_size_light;
	void			*ptr_light;
}				t_scene;


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

#endif
