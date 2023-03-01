/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:48:34 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 19:21:16 by abourbou         ###   ########lyon.fr   */
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
short	tflow_insert_path(t_flow *tflow, t_path *path)
{
	t_dlist	*lpath;
	t_dlist	*new_lpath;
	t_path	*new_path;
	size_t	size_path;

	new_lpath = dlist_new(path);
	if (!new_lpath)
		return (EXIT_FAILURE);
	++tflow->max_flow;
	lpath = tflow->l_path;
	if (!lpath)
		return (tflow_insert_first(tflow, new_lpath));
	new_path = lpath->content;
	size_path = new_path->length;
	if (size_path > path->length)
		return (tflow_insert_front(tflow, new_lpath));
	while (lpath->next && size_path < path->length)
	{
		lpath = lpath->next;
		new_path = lpath->content;
		size_path = new_path->length;
	}
	dlist_pushafter(lpath, new_lpath);
	return (EXIT_SUCCESS);
}
