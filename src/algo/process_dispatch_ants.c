/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispatch_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:46:52 by sachabarane       #+#    #+#             */
/*   Updated: 2023/03/02 19:12:13 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_flow(t_flow *flow)
{
	puts("test flow\n");
	int y = 1;
	for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	{
		printf("Path num %d : \n", y);
		int i = 0;
		y++;
		t_path	*current = cursor->content;
		for (t_dlist *lst_room = current->l_start; lst_room ; lst_room = lst_room->next)
		{
			t_node *room = lst_room->content;
			printf("Room %d : %s\n", i,room->name);
			i++;
		}
		puts("");
	}
}

void	dispatch_ants(t_flow *flow)
{
	print_flow(flow);
	puts("dispatch_ants");
	// ici creation de l'algo de distribution des ants.

}
