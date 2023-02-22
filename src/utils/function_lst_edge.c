/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:07:57 by sbaranes          #+#    #+#             */
/*   Updated: 2021/07/20 10:28:49 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

t_edge	*lstnew_edge(char *vertex1, char *vertex2 , int direction)
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
	lst->prev = NULL;
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
