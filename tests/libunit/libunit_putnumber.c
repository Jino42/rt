/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit_putnumber.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apachkof <apachkof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 22:40:10 by apachkof          #+#    #+#             */
/*   Updated: 2017/11/26 22:44:26 by apachkof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	local_putnbr_fd(int fd, long int n)
{
	long int	nb;
	char		c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	if (nb > 9)
	{
		local_putnbr_fd(fd, nb / 10);
		c = ((nb % 10) + 48);
		write(fd, &c, 1);
	}
	else
	{
		c = nb + 48;
		write(fd, &c, 1);
	}
}
