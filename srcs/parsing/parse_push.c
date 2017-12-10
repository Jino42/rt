#include "rt.h"

bool		parse_push_obj(t_scene *scene, const void * obj, const uint32_t size_obj)
{
	if (!(scene->ptr_obj = ft_memrealloc(scene->ptr_obj, scene->mem_size_obj,
									scene->mem_size_obj + size_obj)) ||
		!(scene->ptr_obj = ft_memcpy_offset(scene->ptr_obj, obj,
									scene->mem_size_obj, size_obj)))
		return (false);
	scene->mem_size_obj += size_obj;
	return (true);
}

bool		parse_push_light(t_scene *scene, const void *obj)
{
	if (!(scene->ptr_light = ft_memrealloc(scene->ptr_light, scene->mem_size_light,
									scene->mem_size_light + sizeof(t_light))) ||
		!(scene->ptr_light = ft_memcpy_offset(scene->ptr_light, obj,
									scene->mem_size_light, sizeof(t_light))))
		return (false);
	scene->mem_size_light += sizeof(t_light);
	return (true);
}
