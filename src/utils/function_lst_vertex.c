
#include "../../include/lib.h"

t_vertex	*lstnew_vertex(char *name, int cord_x, int cord_y)
{
	t_vertex	*lst;

	lst = malloc(sizeof(t_vertex));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup(name);
	lst->cord_x = cord_x;
	lst->cord_y = cord_y;
	lst->next = NULL;
	lst->prev = NULL;
	lst->last = NULL;
	return (lst);
}

void	lstadd_back_vertex(t_vertex **alst, t_vertex *new)
{
	t_vertex	*p;
	t_vertex	*save;

	p = *alst;
	save = *alst;
	if (!alst)
		return ;
	if (!*alst)
	{
		new->last = new;
		*alst = new;
	}
	else if (p)
	{
		p = p->last;
		p->next = new;
		save->last = p->next;
	}
}

void	lstclear_vertex(t_data *data)
{
	t_vertex	*p;
	t_vertex	*lst;

	lst = data->end_vertex;
	while (lst)
	{
		p = lst->next;
		free(lst->name);
		free(lst);
		lst = p;
	}
}
