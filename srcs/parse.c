/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:37:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/08 18:35:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct	s_scene
{
	char		*name;
	t_cam		cam;
	t_light		light;
}				t_scene;


///////////////////////TOOLS
bool		ft_strequ_max(const char *cmp, const char *to, int offset)
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
bool		ft_strequ_arg(const char *cmp, const char *to, int offset)
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
bool		ft_isstralpha(const char *cmp)
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
bool		is_encaps(const char *str, int nb_param) // if fun is ()
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
		i++;
	}
	if (param != nb_param - 1)
		return (false);
	return (true);
}
int		nb_of_arg(const char *str, char c_count, char *c_stop) // nb arg
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
int	count_number_preci(long int n)
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
bool		get_float(char *str, float *nb) // Get Float from STR //ONLY X PRECI ?
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
bool		get_vec(char *str, t_vector *vec)
{
	if (!str)
		return (false);
	if (nb_of_arg(str, ' ', ",)") != 3)
		return (false);
	if (!get_float(strchr_arg_vec(str, 1), &vec->x) ||
		!get_float(strchr_arg_vec(str, 2), &vec->y) ||
		!get_float(strchr_arg_vec(str, 2), &vec->z))
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
bool		parse_light(t_scene *scene, char *line_fd)
{
	if (!is_encaps(line_fd + 5, 4))
		return (false);
	//[1]  ||  POSITION
	if (!get_vec(strchr_arg(line_fd, 1), &scene->light.position))
		return (false);
	//[2]  ||  TYPE LIGHT
	if (ft_strequ_arg(strchr_arg(line_fd, 2), "BASIC", 5))
		scene->light.type = LIGHT_BASIC;
	else if (ft_strequ_arg(strchr_arg(line_fd, 2), "SPHERE", 6))
		scene->light.type = LIGHT_SPHERE;
	else
		return (false);
	//[3]  ||  INTENSITY
	if (!get_float(strchr_arg(line_fd, 3), &scene->light.intensity))
		return (false);
	//[4]  ||  MAKE SPHERE
	if (ft_strequ_max(strchr_arg(line_fd, 4), "AFF", 3))
		;//CREATE SPHERE !!!!!!!!!!!!!
	return (true);
}

bool		parse_scene(t_env *e, char *path)
{
	t_scene scene;
	ft_bzero(&scene, sizeof(t_scene));
	int		fd;
	char	*line_fd;

	(void)e;
	if ((fd = open(path, O_RDWR)) <= 0)
		return (end_of_program(e, "Votre fichier me pose problème.", 0));
	if (!parse_name(&scene, fd))
		return (end_of_program(e, "pars: name error", 0));
	if (!parse_camera(&scene, fd))
		return (end_of_program(e, "pars: camera error", 0));

	line_fd = NULL;
	while (get_next_line(fd, &line_fd) == 1)
	{
		if (line_fd)
		{
			if (ft_strequ_max(line_fd, "light", 5) && line_fd[6])
			{
				if (!parse_light(&scene, line_fd))
					return (end_of_program(e, "pars: light error", 0));
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
