/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:56:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/08 16:32:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libunit.h"

static char		*g_signals[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT",
	"EMT", "FPE", "KILL", "BUSE", "SEGV", "SYS", "PIPE", "ALRM", "TERM", "URG",
	"STOP", "TSTP", "CONT", "CHLD", "TTIN", "TTOU", "IO", "XCPU", "XFSZ",
	"VTALRM", "PROF", "WINCH", "INFO", "USR1", "USR2"};

static int		print_normal_return(char *name, int res)
{
	int len;

	write(2, "    > ", 6);
	len = 0;
	while (name[len])
		len++;
	write(2, name, (len > 25 ? 25: len));
	while (len++ < 25)
		write(2, " ", 1);
	write(2, " : ", 3);
	if (res == EXIT_SUCCESS)
		write(2, "\033[32m[OK]💚", sizeof("\033[32m[OK]💚") - 1);
	else
		write(2, "\033[31m[KO]😂", sizeof("\033[31m[KO]😂") - 1);
	write(2, "\033[0m\n", sizeof("\033[0m\n") - 1);
	return (res);
}

static int		test_signaled(t_unit_test *test, int status)
{
	int			ret;
	int			len;

	ret = WTERMSIG(status);
	if (ret >= 1 && ret <= 31)
	{
		write(2, "    > ", 6);
		len = 0;
		while (test->name[len])
			len++;
		write(2, test->name, (len > 25 ? 25: len));
		while (len++ < 25)
			write(2, " ", 1);
		write(2, " : ", 3);
		write(2, "\033[31m[", sizeof("\033[32m["));
		write(2, g_signals[ret - 1], 4);
		write(2, "]⁉️\033[0m\n", sizeof("]⁉️\033[0m\n"));
	}
	else
		write(2, "Signal inconnu\n", sizeof("Signal inconnu\n"));
	return (EXIT_FAILURE);
}

static int		get_result(t_unit_test *test)
{
	int			status;
	int			ret;

	status = 0;
	wait(&status);
	if (WIFEXITED(status))
		ret = print_normal_return(test->name, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		ret = test_signaled(test, status);
	}
	else
	{
		write(2, "WTF ?\n", sizeof("WTF ?\n"));
		ret = EXIT_FAILURE;
	}
	return (ret);
}

static int		launch_test(t_unit_test *test)
{
	pid_t		pid;
	int			*fd;
	int			*fderr;

	fd = get_fd();
	fderr = get_fderr();
	pid = fork();
	if (pid == -1)
	{
		write(2, "Erreur lors de la création du processus\n",
			sizeof("Erreur lors de la création du processus\n"));
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		alarm(1);
		if (!(redirect_stdout_to_pipe(fd)))
			return (0);
	//	if (!(redirect_stderr_to_pipe(fderr)))
		//	return (0);
		if (test->f() == 0)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
		//close_pipe(fderr);
		close_pipe(fd);
	}
	else
		return (get_result(test));
}

int				launch_tests(t_unit_test **tests)
{
	t_unit_test	*to_be_freed;
	int			ret;
	int			success;
	int			total;

	ret = 0;
	success = 0;
	total = 0;
	while (*tests != NULL)
	{
		ret = (launch_test(*tests) == 0) ? 0 : -1;
		success += (ret + 1);
		++total;
		to_be_freed = *tests;
		*tests = (*tests)->next;
		free(to_be_freed);
	}
	local_putnbr_fd(2, success);
	write(2, "/", 1);
	local_putnbr_fd(2, total);
	write(2, " tests checked\n", sizeof("tests checked\n"));
	return (success == total ? 0 : -1);
}
