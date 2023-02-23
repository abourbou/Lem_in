/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:05:19 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/23 08:12:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	queue_init(t_queue *queue)
{
	queue->start = 0;
	queue->end = 0;
}

void	free_queue(t_queue *queue, void deallocator(void*))
{
	void	*content;

	content = queue_pop(queue);
	while (content)
	{
		if (deallocator)
			deallocator(content);
		content = queue_pop(queue);
	}
}

short	is_queue_empty(t_queue *queue)
{
	return (!queue->start || !queue->end);
}

short	queue_push(t_queue *queue, void *content)
{
	t_dlist	*new_elem;

	new_elem = dlist_new(content);
	if (!new_elem)
		return (EXIT_FAILURE);
	if (!queue->start)
	{
		queue->start = new_elem;
		queue->end = new_elem;
	}
	else
		dlist_pushfront(&queue->start, new_elem);
	return (EXIT_SUCCESS);
}

void	*queue_pop(t_queue *queue)
{
	t_dlist	*prev;
	void	*content;

	if (!queue->start)
		return (0);
	if (queue->start == queue->end)
		queue->start = 0;
	content = queue->end->content;
	prev = queue->end->prev;
	free(queue->end);
	queue->end = prev;
	return (content);
}
