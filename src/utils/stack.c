/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:04:55 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/28 13:15:36 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"


#include "stack.h"

void	free_stack(t_stack *stack, void deallocator(void*))
{
	void	*content;

	content = stack_pop(stack);
	while (content)
	{
		if (deallocator)
			deallocator(content);
		content = stack_pop(stack);
	}
}

short	is_stack_empty(t_stack *stack)
{
	return (!stack->start || !stack->end);
}

short	stack_push(t_stack *stack, void *content)
{
	t_dlist	*new_elem;

	new_elem = dlist_new(content);
	if (!new_elem)
		return (EXIT_FAILURE);
	if (!stack->end)
	{
		stack->start = new_elem;
		stack->end = new_elem;
	}
	else
	{
		stack->end->next = new_elem;
		new_elem->prev = stack->end;
		stack->end = new_elem;
	}
	return (EXIT_SUCCESS);
}

void	*stack_pop(t_stack *stack)
{
	t_dlist	*prev;
	void	*content;

	if (!stack->end)
		return (0);
	content = stack->end->content;
	if (stack->start == stack->end)
		stack->start = 0;
	prev = stack->end->prev;
	free(stack->end);
	stack->end = prev;
	if (prev)
		prev->next = 0;
	return (content);
}
