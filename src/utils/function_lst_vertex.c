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

t_vertex	*lstnew_vertex(char *name, int cord_x, int cord_y)
{
	t_vertex	*lst;

	lst = wrmalloc(sizeof(t_vertex));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup(name);
	lst->cord_x = cord_x;
	lst->cord_y = cord_y;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	lstadd_front_vertex(t_vertex **alst, t_vertex *new)
{
	new->next = *alst;
	*alst = new;
}

void	lstadd_back_vertex(t_vertex **alst, t_vertex *new)
{
	t_vertex	*p;

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

t_vertex	*lstlast_vertex(t_vertex *lstt)
{
	t_vertex	*lst;

	if (!lstt)
		return (lstt);
	lst = lstt;
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
