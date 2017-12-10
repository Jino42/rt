#include "rt.h"

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
