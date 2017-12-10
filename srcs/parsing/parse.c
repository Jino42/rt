#include "rt_parse.h"
#include "rt.h"

static bool		parse_obj(t_env *e, t_scene *scene, char *line_fd, const t_pars *tab)
{
	uint32_t index;

	index = 0;
	while (index < NB_OBJ)
	{
		if (ft_strequ_max(line_fd, tab[index].name, tab[index].offset)
					&& line_fd[tab[index].offset + 1])
		{
			if (!tab[index].parse_obj(scene, line_fd + tab[index].offset))
				return (end_of_program(e, tab[index].msg_error, 0));
			return (true);
		}
		index++;
	}
	return (end_of_program(e, "pars: name fun error", 0));
}

bool		run_parse(t_env *e, const int fd, t_scene *scene, const t_pars *tab)
{
	char	*line_fd;

	if (!parse_name(scene, fd))
		return (end_of_program(e, "pars: name error", 0));
	if (!parse_camera(scene, fd))
		return (end_of_program(e, "pars: camera error", 0));
	line_fd = NULL;
	while (get_next_line(fd, &line_fd) == 1)
	{
		if (line_fd)
		{
			if (!parse_obj(e, scene, line_fd, tab))
			{
				ft_strdel(&line_fd);
				return (false);
			}
			ft_strdel(&line_fd);
		}
	}
	return (true);
}



bool		parse_scene(t_env *e, char *path)
{
	int		fd;
	t_pars	*tab;

	if (!(tab = tab_construct()))
		return (end_of_program(e, "Error de mallocation.", 0));
	if ((fd = open(path, O_RDWR)) <= 0)
		return (end_of_program(e, "Votre fichier me pose problème.", 0));
	if (!run_parse(e, fd, &e->scene, tab))
	{
		tab_destruct(&tab);
		close(fd);
		return (false);
	}
	tab_destruct(&tab);
	close(fd);
	return (true);
}
