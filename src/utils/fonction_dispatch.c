/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachabaranes <sachabaranes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:00:27 by sachabarane       #+#    #+#             */
/*   Updated: 2023/03/03 12:40:32 by sachabarane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

bool	distib_in_path_suite(t_path *current, t_path *current_next)
{
	if (current->nbr_ants + current->length < current_next->nbr_ants
		+ current_next->length)
	{
		current->nbr_ants++;
		return (true);
	}
	return (false);
}

int	get_nb_laps(t_flow *flow)
{
	t_path	*current;

	current = flow->l_path->content;
	return (current->nbr_ants + current->length);
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
