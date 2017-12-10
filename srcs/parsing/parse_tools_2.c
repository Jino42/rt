#include "rt_parse.h"

bool			ft_strequ_max(const char *cmp, const char *to, int offset)
{
	int i;

	i = 0;
	while (cmp[i] && to[i] && i < offset)
	{
		if (cmp[i] != to[i])
			return (false);
		i++;
	}
	if (i < offset)
		return (false);
	return (true);
}

bool			ft_strequ_arg(const char *cmp, const char *to, int offset)
{
	int i;

	i = 0;
	while (cmp[i] && to[i] && i < offset)
	{
		if (cmp[i] != to[i])
			return (false);
		i++;
	}
	if (i < offset)
		return (false);
	while (cmp[i] && cmp[i] == ' ')
		i++;
	if (cmp[i] && (cmp[i] == ',' || cmp[i] == ')'))
		return (true);
	return (false);
}

bool			ft_isstralpha(const char *cmp)
{
	int i;

	i = 0;
	while (cmp[i])
	{
		if (!ft_isalpha(cmp[i]))
			return (false);
		i++;
	}
	return (true);
}

bool			is_encaps(const char *str, int nb_param)
{
	int i;
	int param;

	if (str[0] != '(' || str[ft_strlen(str) - 1] != ')')
		return (false);
	i = 0;
	param = 0;
	while (str[i])
	{
		if (str[i] == ',')
			param++;
		if (str[i] == ')' && str[i + 1])
			return (false);
		if (str[i] == '(' && i)
			return (false);
		i++;
	}
	if (param != nb_param - 1)
		return (false);
	return (true);
}

int				nb_of_arg(const char *str, char c_count, char *c_stop)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && !ft_isin(c_stop, str[i]))
	{
		if (str[i] == c_count)
			count++;
		i++;
	}
	return (count + 1);
}
