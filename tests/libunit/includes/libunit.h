/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:57:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/05 19:35:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H

# define LIBUNIT_H

# define RAZ_COLO "\033[0m"
# define RED_COLO "\033[31m"
# define GRN_COLO "\033[32m"
# define BLD_RED  "\033[1m\033[31m"
# define BLD_GRN  "\033[1m\033[32m"

# define UT_SIZE 1024

typedef struct			s_unit_test
{
	char				*name;
	char				flag;
	int					(*f)(void);

	struct s_unit_test	*next;
}						t_unit_test;

void					load_test(t_unit_test **tests, char *name, char flag, \
		int (*f)(void));
void					local_putnbr_fd(int fd, long int n);
int						launch_tests(t_unit_test **tests);

int						redirect_stdout_to_pipe(int *fd);
void					close_pipe(int *fd);
int						*get_fd(void);
int						get_fd_out(void);
int						get_fd_int(void);

int			redirect_stderr_to_pipe(int *fd);
int			*get_fderr(void);
int			get_fderr_out(void);
int			get_fderr_in(void);

#endif
