/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:41:44 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 22:21:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

short	tflow_insert_first(t_flow *tflow, t_dlist *new_lpath)
{
	tflow->l_path = new_lpath;
	return (EXIT_SUCCESS);
}

short	tflow_insert_front(t_flow *tflow, t_dlist *new_lpath)
{
	dlist_pushfront(&tflow->l_path, new_lpath);
	return (EXIT_SUCCESS);
}

size_t	get_lpath_length(t_dlist *lpath)
{
	t_path	*path;

	path = lpath->content;
	return (path->length);
}

short	tflow_insert_it(t_dlist *lpath, t_dlist *new_lpath, t_dlist *last_lpath)
{
	if (lpath)
		dlist_pushbefore(lpath, new_lpath);
	else
	{
		last_lpath->next = new_lpath;
		new_lpath->prev = last_lpath;
	}
	return (EXIT_SUCCESS);
}

// Insert by ordered size
// Small first
short	tflow_insert_path(t_flow *tflow, t_path *new_path)
{
	t_dlist	*lpath;
	t_dlist	*new_lpath;
	t_dlist	*last_lpath;

	new_lpath = dlist_new(new_path);
	if (!new_lpath)
		return (EXIT_FAILURE);
	++tflow->max_flow;
	lpath = tflow->l_path;
	if (!lpath)
		return (tflow_insert_first(tflow, new_lpath));
	if (get_lpath_length(lpath) > new_path->length)
		return (tflow_insert_front(tflow, new_lpath));
	while (lpath && get_lpath_length(lpath) < new_path->length)
	{
		if (!lpath->next)
			last_lpath = lpath;
		lpath = lpath->next;
	}
	return (tflow_insert_it(lpath, new_lpath, last_lpath));
}
