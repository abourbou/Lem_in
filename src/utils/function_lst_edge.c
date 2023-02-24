/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lst_edge.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:07:57 by sbaranes          #+#    #+#             */
/*   Updated: 2023/02/24 10:58:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_edge	*lstnew_edge(char *vertex1, char *vertex2, int direction)
{
	t_edge	*lst;

	lst = malloc(sizeof(t_edge));
	if (!lst)
		return (NULL);
	lst->vertex1 = ft_strdup(vertex1);
	lst->vertex2 = ft_strdup(vertex2);
	lst->direction = direction;
	lst->last = NULL;
	lst->next = NULL;
	return (lst);
}

void	lstadd_back_edge(t_edge **alst, t_edge *new)
{
	t_edge	*p;
	t_edge	*save;

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

void	lstclear_edge(t_data *data)
{
	t_edge	*p;
	t_edge	*lst;

	if (!data->list_edge)
		return ;
	lst = data->list_edge;
	while (lst)
	{
		p = lst->next;
		free(lst->vertex1);
		free(lst->vertex2);
		free(lst);
		lst = p;
	}
}
