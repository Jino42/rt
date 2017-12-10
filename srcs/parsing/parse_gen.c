#include "rt.h"

/*
** Position
** Couleur
** float
*/

bool		parse_ptr_obj(char *line_fd, t_obj *obj)
{
	if (!get_vec(strchr_arg(line_fd, 1), &obj->position))
		return (false);
	if (!get_hexa(strchr_arg(line_fd, 2), &obj->color))
		return (false);
	if (!get_float(strchr_arg(line_fd, 3), &obj->m_specular))
		return (false);
	return (true);
}

void		parse_basic_param(t_obj *obj, const uint32_t mem_size_obj, const uint32_t obj_id)
{
	ft_bzero(obj, mem_size_obj);
	obj->mem_size_obj = mem_size_obj;
	obj->id = obj_id;
	obj->rotate_speed = 1.5;
	obj->speed = 5;
}
