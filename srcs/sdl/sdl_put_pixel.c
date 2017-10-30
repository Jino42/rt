/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:34:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/29 18:57:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 				sdl_put_pixel(t_sdl *sdl, const uint32_t x,
						const uint32_t y, uint32_t const col)
{
	sdl->pix[x + y * sdl->width] = col;
}
