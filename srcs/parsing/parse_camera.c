/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:49:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:58:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parse.h"

bool		parse_camera(t_scene *scene, const int fd)
{
	char	*line_fd;

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
