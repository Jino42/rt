/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:49:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/12 19:35:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parse.h"

static bool		sphere_aff_light(t_scene *scene, const t_light *light)
{
	t_sphere obj;

	ft_bzero(&obj, sizeof(t_sphere));
	obj.position = light->position;
	obj.radius = 0.3;
	obj.color = 0xFFFFFF;
	obj.m_specular = 0;
	obj.mem_size_obj = sizeof(t_sphere);
	obj.id = OBJ_SPHERE;
	obj.radius2 = obj.radius * obj.radius;
	obj.rotate_speed = 1.5;
	obj.speed = 5;
	obj.flag |= OBJ_ISLIGHT;
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}

bool			parse_light(t_scene *scene, char *line_fd)
{
	t_light		light;

	ft_bzero(&light, sizeof(t_light));
	if (!is_encaps(line_fd, 4))
		return (false);
	if (!get_vec(strchr_arg(line_fd, 1), &light.position))
		return (false);
	if (ft_strequ_arg(strchr_arg(line_fd, 2), "BASIC", 5))
		light.type = LIGHT_BASIC;
	else
		return (false);
	if (!get_float(strchr_arg(line_fd, 3), &light.intensity))
		return (false);
	if (ft_strequ_arg(strchr_arg(line_fd, 4), "AFF", 3))
	{
		if (!sphere_aff_light(scene, &light))
			return (false);
	}
	else
		return (false);
	if (!parse_push_light(scene, (void *)&light))
		return (false);
	return (true);
}
