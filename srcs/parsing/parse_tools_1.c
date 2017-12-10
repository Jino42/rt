#include "rt.h"

char			*strchr_arg(char *str, int arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		if (str[i] == '(' && arg == 1)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == ',' || str[i] == ')')
				return (NULL);
			return (str + i);
		}
		else if (str[i] == ',' && count + 1 == arg)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == ',' || str[i] == ')')
				return (NULL);
			return (str + i);
		}
		i++;
	}
	return (NULL);
}

char			*strchr_arg_vec(char *str, int arg)
{
	int i;
	int count;

	if (arg == 1 || !arg)
		return (str);

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		if (str[i] == ' ' && count + 1 == arg)
			return (str + i + 1);
		i++;
	}
	return (NULL);
}

int				rt_count_number_preci(long int n)
{
	int i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
