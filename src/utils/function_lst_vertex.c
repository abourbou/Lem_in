
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
	t_vertex	*temp;
	t_vertex	*lst;

	if (data->list_vertex == NULL)
		return ;
	lst = data->list_vertex;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp->name);
		free(temp);
	}
	free(data->start_vertex->name);
	free(data->start_vertex);
	free(data->end_vertex->name);
	free(data->end_vertex);
}

void	set_vertex(t_data *data, t_vertex *new_vertex, int code)
{
	data->dico_vertex = add_node(data->dico_vertex, new_vertex->name);
	if (code == 0)
		data->start_vertex = new_vertex;
	else
		data->end_vertex = new_vertex;
}
