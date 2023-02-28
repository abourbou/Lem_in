/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:05:38 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/28 13:15:40 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

#include "lib.h"

typedef struct s_stack
{
	t_dlist	*start;
	t_dlist	*end;
}	t_stack;

void	free_stack(t_stack *stack, void deallocator(void*));
short	is_stack_empty(t_stack *stack);
short	stack_push(t_stack *stack, void *content);
void	*stack_pop(t_stack *stack);

#endif