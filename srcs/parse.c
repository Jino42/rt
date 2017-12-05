/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:37:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/05 15:45:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		parse_scene(t_env *e, char *path)
{
	int		fd;
	char	*line_fd;

	(void)e;
	fd = open(path, O_RDWR);
	while (get_next_line(fd, &line_fd) == 1)
		ft_printf("%s\n", line_fd);
	close(fd);
	return (true);
}
