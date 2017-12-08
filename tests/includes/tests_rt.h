/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_rt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 18:45:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/08 19:00:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_RT_H
# define TESTS_RT_H

# include "libunit.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>

# define PATH_RT /Users/ntoniolo/base/rt/tests/tests_gen

# define RUN_RT(file_tested, diff, flag) int pid = 0, fd[2], status = 0; \
	char	buffer[UT_SIZE + 1]; \
	char	path_rt[200] = "/Users/ntoniolo/base/rt/tests/";\
	if (file_tested) \
		strcat(path_rt, file_tested); \
	bzero(buffer, UT_SIZE + 1); \
 \
	if (pipe(fd)) \
		return (-1); \
	pid = fork(); \
	if (pid) \
	{ \
		close(fd[1]); \
		wait(&status); \
		read(fd[0], buffer, UT_SIZE); \
		if (flag) \
			ft_dprintf(2, "[%s]\n", buffer); \
		close(fd[0]); \
	} \
	else \
	{ \
		close(fd[0]); \
		dup2(fd[1], 2); \
		char *args[] = { "rt", "-debug_p", path_rt, NULL}; \
		if (execv("/Users/ntoniolo/base/rt/rt", args) == -1) \
		{ \
			ft_dprintf(2, "Erreur lors de l'execution\n"); \
			return EXIT_FAILURE; \
		} \
	} \
	if (!strcmp(buffer, diff)) \
		return (0); \
	else \
		return (-1);

# define NB_TEST 4

int				tests_gen_launcher(void);
int				tests_camera_launcher(void);
int				tests_light_launcher(void);
int				tests_obj_ccp_launcher(void);

#endif
