/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:57:58 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 21:59:40 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	dlist_pushbefore(t_dlist *elem, t_dlist *new_elem)
{
	t_dlist	*prev_elem;

	prev_elem = elem->prev;
	elem->prev = new_elem;
	new_elem->next = elem;
	new_elem->prev = prev_elem;
	if (prev_elem)
		prev_elem->next = new_elem;
}

// Push new_elem after elem
void	dlist_pushafter(t_dlist *elem, t_dlist *new_elem)
{
	t_dlist	*next_elem;

	next_elem = elem->next;
	elem->next = new_elem;
	new_elem->prev = elem;
	new_elem->next = next_elem;
	if (next_elem)
		next_elem->prev = new_elem;
}
