# include <stdlib.h>
# include <unistd.h>
# include <string.h>
typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void	*ft_memalloc(size_t size)
{
	void *tab;

	if (!(tab = malloc(size)))
		exit(0);
	if (tab == NULL)
		return (NULL);
	bzero(tab, size);
	return (tab);
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if (!(lst = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(lst->content = (void*)ft_memalloc(content_size)))
			return (NULL);
		memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
	}
	else
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	lst->next = NULL;
	return (lst);
}

int			ft_lstlen(const t_list *l)
{
	int i;

	i = 0;
	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

void	ft_lstinsert(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
		ft_lstinsert(&((*alst)->next), new);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

int			ft_faequal(float a, float b)
{
	if (a - b < 0)
	{
		if ((a - b) * -1 < 0.00005)
			return (1);
		else
			return (0);
	}
	if ((a - b) < 0.00005)
		return (1);
	return (0);
}
