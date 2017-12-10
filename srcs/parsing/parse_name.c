#include "rt.h"

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
