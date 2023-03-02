/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:48:34 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 22:07:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_flow	*init_tflow(void)
{
	t_flow	*tflow;

	tflow = malloc(sizeof(t_flow));
	if (!tflow)
	{
		print_error("can not malloc in create_tflow");
		return (0);
	}
	tflow->l_path = 0;
	tflow->max_flow = 0;
	return (tflow);
}

void	free_tflow(t_flow *tflow)
{
	t_dlist	*l_path;
	t_dlist	*l_next_path;
	t_path	*path;
	t_dlist	*l_current_room;
	t_dlist	*l_next_room;

	l_path = tflow->l_path;
	while (l_path)
	{
		path = l_path->content;
		l_current_room = path->l_start;
		while (l_current_room)
		{
			l_next_room = l_current_room->next;
			free(l_current_room);
			l_current_room = l_next_room;
		}
		free(path);
		l_next_path = l_path->next;
		free(l_path);
		l_path = l_next_path;
	}
}

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

// Insert by ordered size
// Small first
short	tflow_insert_path(t_flow *tflow, t_path *new_path)
{
	t_dlist	*lpath;
	t_path	*current_path;
	t_dlist	*new_lpath;
	size_t	size_current_path;
	t_dlist	*last_lpath;

	new_lpath = dlist_new(new_path);
	if (!new_lpath)
		return (EXIT_FAILURE);
	++tflow->max_flow;
	lpath = tflow->l_path;
	if (!lpath)
		return (tflow_insert_first(tflow, new_lpath));
	current_path = lpath->content;
	size_current_path = current_path->length;
	// Special case of if the new elem is first
	if (size_current_path > new_path->length)
		return (tflow_insert_front(tflow, new_lpath));
	// Else find the first elem to be larger than new_path
	while (lpath)
	{
		current_path = lpath->content;
		size_current_path = current_path->length;
		if (size_current_path > new_path->length)
			break;
		if (!lpath->next)
			last_lpath = lpath;
		lpath = lpath->next;
	}
	if (lpath)
		dlist_pushbefore(lpath, new_lpath);
	else
	{
		last_lpath->next = new_lpath;
		new_lpath->prev = last_lpath;
	}
	return (EXIT_SUCCESS);
}
