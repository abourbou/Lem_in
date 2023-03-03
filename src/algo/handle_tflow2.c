/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tflow2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:40:36 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 12:42:50 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	free_path(t_path *path)
{
	t_dlist	*current;
	t_dlist	*next;

	current = path->l_start;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(path);
}

short	path_insert(t_path *path, t_node *node)
{
	if (!path->l_start || !path->l_end)
	{
		path->l_start = dlist_new(node);
		if (!path->l_start)
			return (EXIT_FAILURE);
		path->l_end = path->l_start;
		return (EXIT_SUCCESS);
	}
	path->l_end->next = dlist_new(node);
	if (!path->l_end->next)
		return (EXIT_FAILURE);
	path->l_end->next->prev = path->l_end;
	path->l_end = path->l_end->next;
	return (EXIT_SUCCESS);
}

t_path	*free_ret_path(t_path *path)
{
	free(path);
	return (0);
}
