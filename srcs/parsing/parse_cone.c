#include "rt_parse.h"

bool		parse_cone(t_scene *scene, char *line_fd)
{
	t_cone obj;

	parse_basic_param((t_obj *)&obj, sizeof(t_cone), OBJ_CONE);
	if (!is_encaps(line_fd, 5))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	//[4]  ||  ANGLE
	if (!get_float(strchr_arg(line_fd, 4), &obj.angle))
		return (false);
	//[5]  ||  LIMIT
	if (!get_float(strchr_arg(line_fd, 5), &obj.limit))
		return (false);
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
