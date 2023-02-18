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

t_random	*lstnew_random(char *name)
{
	t_random	*lst;

	lst = wrmalloc(sizeof(t_random));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	lstadd_front_random(t_random **alst, t_random *new)
{
	new->next = *alst;
	*alst = new;
}

void	lstadd_back_random(t_random **alst, t_random *new)
{
	t_random	*p;

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

t_random	*lstlast_random(t_random *lstt)
{
	t_random	*lst;

	if (!lstt)
		return (lstt);
	lst = lstt;
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
