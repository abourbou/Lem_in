/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:48:12 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/23 16:50:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

size_t dlist_compt(t_dlist *list)
{
	size_t	compt;

	compt = 0;
	while (list)
	{
		++compt;
		list = list->next;
	}
	return (compt);
}