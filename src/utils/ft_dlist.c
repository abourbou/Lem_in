/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:14:27 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 17:59:52 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_dlist	*dlist_new(void *content)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	new->content = content;
	new->next = 0;
	new->prev = 0;
	return (new);
}

void	dlist_pushfront(t_dlist **start, t_dlist *new_elem)
{
	if (!start)
		return ;
	if (!*start)
	{
		*start = new_elem;
		return ;
	}
	new_elem->next = *start;
	(*start)->prev = new_elem;
	*start = new_elem;
}

void	dlist_erase(t_dlist **start, t_dlist *elem)
{
	t_dlist	*prev;
	t_dlist	*next;

	if (!start || !*start)
		return ;
	prev = elem->prev;
	next = elem->next;
	if (*start == elem)
		*start = elem->next;
	free(elem);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

size_t	dlist_compt(t_dlist *list)
{
	size_t	compt;

	compt = 0;
	while (list)
	{
		++compt;
		list = list->next;
	}
	return (compt);
}
