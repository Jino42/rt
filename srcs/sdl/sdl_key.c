/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:39:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 16:43:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_sdl.h"

bool		sdl_key(t_sdl *sdl, const uint32_t key)
{
	if (sdl->event.key[key])
		return (true);
	return (false);
}
