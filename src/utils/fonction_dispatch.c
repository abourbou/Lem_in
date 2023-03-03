/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:00:27 by sachabarane       #+#    #+#             */
/*   Updated: 2023/03/03 08:34:47 by sbaranes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"


void	set_current_capasity(t_dlist *actual)
{
	int		capacity_to_set;
	t_dlist	*cursor;
	t_path	*current;

	cursor = actual;
	current = cursor->content;
	capacity_to_set = current->capacity;
	while (cursor)
	{
		current = cursor->content;
		current->capacity = capacity_to_set;
		current->nbr_ants = 0;
		cursor = cursor->prev;
	}
}

bool	set_roolback(t_flow *flow, t_dlist *cursor, t_path *current)
{
	t_path	*prev;

	if (cursor->prev != NULL)
	{
		prev = cursor->prev->content;
		if (prev->capacity < current->capacity)
		{
			if (flow->ants_left >= (prev->capacity + current->capacity))
			{
				set_current_capasity(cursor);
				return (true);
			}
		}
	}
	return (false);
}

void	resize_capacity(t_flow *flow, t_dlist *cursor, t_path *current)
{
	t_path	*next;

	if (cursor->next != NULL)
	{
		next = cursor->next->content;
		if (current->capacity != next->capacity)
		{
			if ((current->capacity + 1) != next->capacity
				|| (current->capacity + 1) < flow->ants_left)
				{
					current->capacity = next->capacity;
				}
		}
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((48 + nb % 10));
}

void	ft_putstr(char *line)
{
	write(1, line, ft_strlen(line));
}
