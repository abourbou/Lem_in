/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:24:35 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 19:19:19 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "graph.h"
# include "queue.h"

# define MAX_UNSIGN_INT 4294967295

// Preprocessing algo
short	check_path_exists(t_graph *graph);

// Level graph functions
int		construct_level_graph(t_graph *graph);

// Find blocking path
void	find_blocking_path(t_graph *graph, size_t *flow, size_t max_theor_flow);

// Dinic algorithm
short	can_access_residual_node(t_link *link, t_node *head);
void	increment_flow(t_link *link, t_node *source, t_node *dest);
size_t	find_theory_maxflow(t_graph *graph);
t_flow	*dinic_algo(t_graph *graph);

// t_flow utils
t_flow	*create_tflow(t_graph *graph, t_flow *tflow);
short	is_node_accessible(t_link *link, t_node *tail, t_node *head);

// function for ants mooving
void	dispatch_ants(t_flow *l_flow, unsigned int nb_ants);
void	moove_all_by_one(t_flow *flow, t_path *path);
void	run_ants_and_print_moove(t_flow *flow, unsigned int ants_nb);
void	print_path(t_path *path);

t_flow	init_path(int path_nb); // temps
void	print_flow(t_flow *flow); // temps

#endif
