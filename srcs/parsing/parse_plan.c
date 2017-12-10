#include "rt.h"

bool		parse_plan(t_scene *scene, char *line_fd)
{
	t_plan obj;

	parse_basic_param((t_obj *)&obj, sizeof(t_plan), OBJ_PLANE);
	obj.normal = vector_construct(0, 0, 1);
	if (!is_encaps(line_fd, 3))
		return (false);
	if (!parse_ptr_obj(line_fd, (t_obj *)&obj))
		return (false);
	if (!parse_push_obj(scene, (void *)&obj, obj.mem_size_obj))
		return (false);
	return (true);
}
