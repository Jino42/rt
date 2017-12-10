#ifndef RT_PARSE_H
# define RT_PARSE_H

# include "rt_obj.h"

# include <stdbool.h>
# include <stdint.h>

typedef struct	s_pars
{
	char		*name;
	bool		(*parse_obj)(t_scene *, char *);
	uint32_t	offset;
	char		*msg_error;
}				t_pars;

bool			ft_strequ_max(const char *cmp, const char *to, int offset);
bool			ft_strequ_arg(const char *cmp, const char *to, int offset);
bool			ft_isstralpha(const char *cmp);
bool			is_encaps(const char *str, int nb_param);
int				nb_of_arg(const char *str, char c_count, char *c_stop);
char			*strchr_arg(char *str, int arg);
char			*strchr_arg_vec(char *str, int arg);
int				rt_count_number_preci(long int n);

bool			get_float(char *str, float *nb);
bool			get_radius(char *str, float *radius, float *radius2);
bool			get_hexa(char *str, uint32_t *nb);
bool			get_vec(char *str, t_vector *vec);

void			parse_basic_param(t_obj *obj, const uint32_t mem_size_obj, const uint32_t obj_id);
bool			parse_ptr_obj(char *line_fd, t_obj *obj);

t_pars			*tab_construct(void);
void 			tab_destruct(t_pars **pars);

bool			parse_push_obj(t_scene *scene, const void * obj, const uint32_t size_obj);
bool			parse_push_light(t_scene *scene, const void *obj);

bool			parse_sphere(t_scene *scene, char *line_fd);
bool			parse_ellipsoid(t_scene *scene, char *line_fd);
bool			parse_cone(t_scene *scene, char *line_fd);
bool			parse_cylinder(t_scene *scene, char *line_fd);
bool			parse_paraboloid(t_scene *scene, char *line_fd);
bool			parse_ellipsoid(t_scene *scene, char *line_fd);
bool			parse_plan(t_scene *scene, char *line_fd);
bool			parse_light(t_scene *scene, char *line_fd);

bool			parse_name(t_scene *scene, const int fd);
bool			parse_camera(t_scene *scene, const int fd);

#endif
