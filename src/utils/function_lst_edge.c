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

	lst = wrmalloc(sizeof(t_edge));
	if (!lst)
		return (NULL);
	lst->vertex1 = ft_strdup(vertex1);
	lst->vertex2 = ft_strdup(vertex2);
	lst->direction = direction;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	lstadd_front_edge(t_edge **alst, t_edge *new)
{
	new->next = *alst;
	*alst = new;
}

void	lstadd_back_edge(t_edge **alst, t_edge *new)
{
	t_edge	*p;

	p = *alst;
	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else if (p)
	{
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_edge	*lstlast_edge(t_edge *lstt)
{
	t_edge	*lst;

	if (!lstt)
		return (lstt);
	lst = lstt;
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
