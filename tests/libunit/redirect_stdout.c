/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:19:49 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/05 19:35:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <unistd.h>

int			redirect_stdout_to_pipe(int *fd)
{
	if (pipe(fd) != 0)
		return (0);
	dup2(fd[1], 1);
	return (1);
}

void		close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int			*get_fd(void)
{
	static int fd[2] = {0, 0};

	return (fd);
}

int			get_fd_out(void)
{
	int *fd;

	fd = get_fd();
	return (fd[0]);
}

int			get_fd_in(void)
{
	int *fd;

	fd = get_fd();
	return (fd[1]);
}

int			redirect_stderr_to_pipe(int *fd)
{
	if (pipe(fd) != 0)
		return (0);
	dup2(fd[1], 2);
	return (1);
}

int			*get_fderr(void)
{
	static int fd[2] = {0, 0};

	return (fd);
}

int			get_fderr_out(void)
{
	int *fd;

	fd = get_fderr();
	return (fd[0]);
}

int			get_fderr_in(void)
{
	int *fd;

	fd = get_fderr();
	return (fd[1]);
}
