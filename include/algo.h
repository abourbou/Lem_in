/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:24:35 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/27 16:40:23 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "graph.h"
# include "queue.h"

# define MAX_UNSIGN_INT 4294967295

// Preprocessing algo
short	check_path_exists(t_graph *graph);
void	erase_dead_end_nodes(t_graph *graph);

// Level graph functions
int		construct_level_graph(t_graph *graph);

// Utils algo
short	can_access_node(t_link *link, t_node *head);

// Dinic algorithm
size_t	find_theory_maxflow(int nb_ants, t_graph *graph);
t_flow	*dinic_algo(int nb_ants, t_graph *graph);

#endif