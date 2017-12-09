/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:37:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/09 18:28:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

///////////////////////TOOLS
bool			ft_strequ_max(const char *cmp, const char *to, int offset)
{
	int i;

	i = 0;
	while (cmp[i] && to[i] && i < offset)
	{
		if (cmp[i] != to[i])
			return (false);
		i++;
	}
	if (i < offset)
		return (false);
	return (true);
}
bool			ft_strequ_arg(const char *cmp, const char *to, int offset)
{
	int i;

	i = 0;
	while (cmp[i] && to[i] && i < offset)
	{
		if (cmp[i] != to[i])
			return (false);
		i++;
	}
	if (i < offset)
		return (false);
	while (cmp[i] && cmp[i] == ' ')
		i++;
	if (cmp[i] && (cmp[i] == ',' || cmp[i] == ')'))
		return (true);
	return (false);
}
bool			ft_isstralpha(const char *cmp)
{
	int i;

	i = 0;
	while (cmp[i])
	{
		if (!ft_isalpha(cmp[i]))
			return (false);
		i++;
	}
	return (true);
}
bool			is_encaps(const char *str, int nb_param) // if fun is ()
{
	int i;
	int param;

	if (str[0] != '(' || str[ft_strlen(str) - 1] != ')')
		return (false);
	i = 0;
	param = 0;
	while (str[i])
	{
		if (str[i] == ',')
			param++;
		if (str[i] == ')' && str[i + 1])
			return (false);
		if (str[i] == '(' && i)
			return (false);
		i++;
	}
	if (param != nb_param - 1)
		return (false);
	return (true);
}
int				nb_of_arg(const char *str, char c_count, char *c_stop) // nb arg
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && !ft_isin(c_stop, str[i]))
	{
		if (str[i] == c_count)
			count++;
		i++;
	}
	return (count + 1);
}
char			*strchr_arg(char *str, int arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		if (str[i] == '(' && arg == 1)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == ',' || str[i] == ')')
				return (NULL);
			return (str + i);
		}
		else if (str[i] == ',' && count + 1 == arg)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == ',' || str[i] == ')')
				return (NULL);
			return (str + i);
		}
		i++;
	}
	return (NULL);
}
char			*strchr_arg_vec(char *str, int arg)
{
	int i;
	int count;

	if (arg == 1 || !arg)
		return (str);

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		if (str[i] == ' ' && count + 1 == arg)
			return (str + i + 1);
		i++;
	}
	return (NULL);
}
int				count_number_preci(long int n)
{
	int i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
bool			get_float(char *str, float *nb) // Get Float from STR //ONLY X PRECI ?
{
	int i = 0;
	int	preci = 0;
	bool in = false;

	*nb = ft_atoi(str);
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '.')
		{
			if (in)
				return (false);
			in = true;
			preci = ft_atoi(str + i + 1);
			*nb += (preci / pow(10, count_number_preci(preci)));
		}
		i++;
	}
	return (true);
}
bool			get_hexa(char *str, uint32_t *nb) // Get Float from STR //ONLY X PRECI ?
{
	*nb = ft_atoi_base(str, 16);
	return (true);
}
bool			get_vec(char *str, t_vector *vec)
{
	if (!str)
		return (false);
	if (nb_of_arg(str, ' ', ",)") != 3)
		return (false);
	if (!get_float(strchr_arg_vec(str, 1), &vec->x) ||
		!get_float(strchr_arg_vec(str, 2), &vec->y) ||
		!get_float(strchr_arg_vec(str, 3), &vec->z))
		return (false);
	return (true);
}

////////////////////////ONE BY ONE

bool		parse_name(t_scene *scene, const int fd)
{
	char	*line_fd;

	line_fd = NULL;
	if (get_next_line(fd, &line_fd) != 1)
	{
		ft_strdel(&line_fd);
		return (false);
	}
	if (!ft_strequ_max(line_fd, "name:", 5) || !line_fd[5])
		return (false);
	if (!ft_isstralpha(line_fd + 5))
		return (false);
	scene->name = ft_strdup(line_fd + 5);
	ft_strdel(&line_fd);
	return (true);
}
bool		parse_camera(t_scene *scene, const int fd)
{
	char	*line_fd;

	(void)scene;
	line_fd = NULL;
	if (get_next_line(fd, &line_fd) != 1)
	{
		ft_strdel(&line_fd);
		return (false);
	}
	if (!ft_strequ_max(line_fd, "camera", 6) || !line_fd[7])
		return (false);
	if (!is_encaps(line_fd + 6, 1))
		return (false);
	if (!get_vec(strchr_arg(line_fd, 1), &scene->cam.position))
		return (false);
	ft_strdel(&line_fd);
	return (true);
}
bool		parse_ptr_obj(char *line_fd, t_obj *obj)
{
	//[1]  ||  POSITION
	if (!get_vec(strchr_arg(line_fd, 1), &obj->position))
		return (false);
	//[2]  ||  COULEUR
	if (!get_hexa(strchr_arg(line_fd, 2), &obj->color))
		return (false);
	//[3]  ||  COULEUR
	if (!get_float(strchr_arg(line_fd, 3), &obj->m_specular))
		return (false);
	return (true);
}


bool		parse_push_obj(t_scene *scene, const void * obj, const uint32_t size_obj)
{
	if (!(scene->ptr_obj = ft_memrealloc(scene->ptr_obj, scene->mem_size_obj,
									scene->mem_size_obj + size_obj)) ||
		!(scene->ptr_obj = ft_memcpy_offset(scene->ptr_obj, obj,
									scene->mem_size_obj, size_obj)))
		return (false);
	scene->mem_size_obj += size_obj;
	return (true);
}
bool		parse_push_light(t_scene *scene, const void *obj)
{
	if (!(scene->ptr_light = ft_memrealloc(scene->ptr_light, scene->mem_size_light,
									scene->mem_size_light + sizeof(t_light))) ||
		!(scene->ptr_light = ft_memcpy_offset(scene->ptr_light, obj,
									scene->mem_size_light, sizeof(t_light))))
		return (false);
	scene->mem_size_light += sizeof(t_light);
	return (true);
}
bool		parse_cone(t_scene *scene, char *line_fd)
{
	t_cone obj;

	(void)scene;
	ft_bzero(&obj, sizeof(t_cone));
	if (!is_encaps(line_fd, 5))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  ANGLE
	if (!get_float(strchr_arg(line_fd, 4), &obj.angle))
		return (false);
	//[5]  ||  LIMIT
	if (!get_float(strchr_arg(line_fd, 5), &obj.limit))
		return (false);
	obj.mem_size_obj = sizeof(t_cone);
	obj.id = OBJ_CONE;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool		parse_paraboloid(t_scene *scene, char *line_fd)
{
	t_paraboloid obj;

	(void)scene;
	ft_bzero(&obj, sizeof(t_paraboloid));
	if (!is_encaps(line_fd, 5))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  ANGLE
	if (!get_float(strchr_arg(line_fd, 4), &obj.option))
		return (false);
	//[5]  ||  LIMIT
	if (!get_float(strchr_arg(line_fd, 5), &obj.limit))
		return (false);
	obj.mem_size_obj = sizeof(t_paraboloid);
	obj.id = OBJ_PARABOLOID;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool		parse_cylinder(t_scene *scene, char *line_fd)
{
	t_cylinder obj;

	(void)scene;
	ft_bzero(&obj, sizeof(t_cylinder));
	if (!is_encaps(line_fd, 5))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  ANGLE
	if (!get_float(strchr_arg(line_fd, 4), &obj.radius))
		return (false);
	//[5]  ||  LIMIT
	if (!get_float(strchr_arg(line_fd, 5), &obj.limit))
		return (false);
	obj.mem_size_obj = sizeof(t_cylinder);
	obj.id = OBJ_CYLINDER;
	obj.radius2 = obj.radius * obj.radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool		parse_sphere(t_scene *scene, char *line_fd, const uint32_t flag)
{
	t_sphere obj;

	ft_bzero(&obj, sizeof(t_sphere));
	if (!is_encaps(line_fd, 4))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  RADIUS
	if (!get_float(strchr_arg(line_fd, 4), &obj.radius))
		return (false);
	obj.mem_size_obj = sizeof(t_sphere);
	obj.id = OBJ_SPHERE;
	obj.radius2 = obj.radius * obj.radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.flag = flag;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool		parse_plan(t_scene *scene, char *line_fd)
{
	t_plan obj;

	(void)scene;
	ft_bzero(&obj, sizeof(t_plan));
	if (!is_encaps(line_fd, 3))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	obj.mem_size_obj = sizeof(t_plan);
	obj.id = OBJ_PLANE;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.normal = vector_construct(0, 0, 1);
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool		parse_ellipsoid(t_scene *scene, char *line_fd)
{
	t_ellipsoid obj;

	(void)scene;
	ft_bzero(&obj, sizeof(t_ellipsoid));
	if (!is_encaps(line_fd, 5))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  ANGLE
	if (!get_float(strchr_arg(line_fd, 4), &obj.radius))
		return (false);
	//[5]  ||  SIZE XYZ
	if (!get_vec(strchr_arg(line_fd, 5), &obj.size))
		return (false);
	obj.mem_size_obj = sizeof(t_ellipsoid);
	obj.id = OBJ_ELLIPSOID;
	obj.radius2 = obj.radius * obj.radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
bool 		sphere_aff_light(t_scene *scene, const t_light *light)
{
	t_sphere obj;
	ft_bzero(&obj, sizeof(t_sphere));
	obj.position = light->position;
	obj.radius = 0.3;
	obj.color = 0xFFFFFF;
	obj.m_specular = 0;
	obj.mem_size_obj = sizeof(t_sphere);
	obj.id = OBJ_SPHERE;
	obj.radius2 = obj.radius * obj.radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.flag |= F_ISLIGHT;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}

bool		parse_light(t_scene *scene, char *line_fd)
{
	t_light		light;

	ft_bzero(&light, sizeof(t_light));
	if (!is_encaps(line_fd + 5, 4))
		return (false);
	//[1]  ||  POSITION
	if (!get_vec(strchr_arg(line_fd, 1), &light.position))
		return (false);
	//[2]  ||  TYPE LIGHT
	if (ft_strequ_arg(strchr_arg(line_fd, 2), "BASIC", 5))
		light.type = LIGHT_BASIC;
	else if (ft_strequ_arg(strchr_arg(line_fd, 2), "SPHERE", 6))
		light.type = LIGHT_SPHERE;
	else
		return (false);
	//[3]  ||  INTENSITY
	if (!get_float(strchr_arg(line_fd, 3), &light.intensity))
		return (false);
	//[4]  ||  MAKE SPHERE
	if (ft_strequ_arg(strchr_arg(line_fd, 4), "AFF", 3))
	{
		if (!sphere_aff_light(scene, &light))
			return (false);
	}
	else
		return (false);
	if (!parse_push_light(scene, (void *)&light))
		return (false);
	return (true);
}

bool		parse_scene(t_env *e, char *path)
{
	t_scene	*scene;
	int		fd;
	char	*line_fd;

	scene = &e->scene;
	if ((fd = open(path, O_RDWR)) <= 0)
		return (end_of_program(e, "Votre fichier me pose problème.", 0));
	if (!parse_name(scene, fd))
		return (end_of_program(e, "pars: name error", 0));
	if (!parse_camera(scene, fd))
		return (end_of_program(e, "pars: camera error", 0));

	line_fd = NULL;
	while (get_next_line(fd, &line_fd) == 1)
	{
		if (line_fd)
		{
			if (ft_strequ_max(line_fd, "light", 5) && line_fd[6])
			{
				if (!parse_light(scene, line_fd))
					return (end_of_program(e, "pars: light error", 0));
			}
			else if (ft_strequ_max(line_fd, "cone", 4) && line_fd[5])
			{
				if (!parse_cone(scene, line_fd + 4))
					return (end_of_program(e, "pars: cone error", 0));
			}
			else if (ft_strequ_max(line_fd, "paraboloid", 10) && line_fd[11])
			{
				if (!parse_paraboloid(scene, line_fd + 10))
					return (end_of_program(e, "pars: paraboloid error", 0));
			}
			else if (ft_strequ_max(line_fd, "cylinder", 8) && line_fd[9])
			{
				if (!parse_cylinder(scene, line_fd + 8))
					return (end_of_program(e, "pars: cylinder error", 0));
			}
			else if (ft_strequ_max(line_fd, "sphere", 6) && line_fd[7])
			{
				if (!parse_sphere(scene, line_fd + 6, 0))
					return (end_of_program(e, "pars: sphere error", 0));
			}
			else if (ft_strequ_max(line_fd, "plan", 4) && line_fd[5])
			{
				if (!parse_plan(scene, line_fd + 4))
					return (end_of_program(e, "pars: plan error", 0));
			}
			else if (ft_strequ_max(line_fd, "ellipsoid", 9) && line_fd[10])
			{
				if (!parse_ellipsoid(scene, line_fd + 9))
					return (end_of_program(e, "pars: ellipsoid error", 0));
			}
			else
			{
				ft_strdel(&line_fd);
				return (end_of_program(e, "parse: function name error", 0));
			}
			ft_strdel(&line_fd);
		}
	}
	close(fd);
	return (true);
}
