#include "rt.h"

static void 		tab_put_param(t_pars *tab, const char *name,
					bool (*f)(t_scene *, char *), const char *msg_error)
{
	tab->offset = ft_strlen(name);
	tab->parse_obj = f;
	tab->msg_error = ft_strdup(msg_error);
	tab->name = ft_strdup(name);
}

t_pars		*tab_construct(void)
{
	t_pars		*tab;

	if (!(tab = ft_memalloc(sizeof(t_pars) * NB_OBJ)))
		return (NULL);
	tab_put_param(&tab[0], "light", &parse_light,
									"pars: light error");
	tab_put_param(&tab[1], "cone", &parse_cone,
									"pars: cone error");
	tab_put_param(&tab[2], "paraboloid", &parse_paraboloid,
									"pars: paraboloid error");
	tab_put_param(&tab[3], "cylinder", &parse_cylinder,
									"pars: cylinder error");
	tab_put_param(&tab[4], "sphere", &parse_sphere,
									"pars: sphere error");
	tab_put_param(&tab[5], "plan", &parse_plan,
									"pars: plan error");
	tab_put_param(&tab[6], "ellipsoid", &parse_ellipsoid,
									"pars: ellipsoid error");
	return (tab);
}

void 		tab_destruct(t_pars **pars)
{
	int i;

	i = 0;
	while (i < NB_OBJ)
	{
		ft_strdel(&((*pars)->name));
		ft_strdel(&((*pars)->msg_error));
		i++;
	}
	*pars = NULL;
}
