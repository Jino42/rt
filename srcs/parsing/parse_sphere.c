#include "rt_parse.h"

bool		parse_sphere(t_scene *scene, char *line_fd)
{
	t_sphere obj;

	parse_basic_param((t_obj *)&obj, sizeof(t_sphere), OBJ_SPHERE);
	if (!is_encaps(line_fd, 4))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	if (!get_radius(strchr_arg(line_fd, 4), &obj.radius, &obj.radius2))
		return (false);
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
