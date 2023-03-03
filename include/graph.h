/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:38:52 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 12:41:30 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include "lib.h"

/*
******************** Struct ********************
*/
/**
 * Node structure containing:
 *  - name
 *  - l_links : list links connected to the node
 *  - is_used : is the room already use for dfs or other algorithm
 *  - ant_nb : number of the ant in the room, 0 means the room is empty
*/
typedef struct s_node
{
	char			*name;
	t_dlist			*l_links;
	short			is_used;
	unsigned int	level;
	int				ant_nb;
	struct s_node	*node_out;
}	t_node;

/**
 * Link structure containing:
 * - terminal : node where it goes
 * - flow : status of the link
 * (0 = unused, 1 = node1->node2)
*/
typedef struct s_link
{
	t_node	*node1;
	t_node	*node2;
	int		flow;
}	t_link;

/**
 * Graph structure containing:
 *  - list of nodes in the graph
 *  - start node
 *  - end node
*/
typedef struct s_graph
{
	t_dlist			*l_node;
	t_node			*start_node;
	t_node			*end_node;
	unsigned int	nb_ants;
}	t_graph;

typedef struct s_path
{
	t_dlist			*l_start;
	t_dlist			*l_end;
	unsigned int	length;
	unsigned int	nbr_ants;
	unsigned int	capacity;
}	t_path;

// flow of a graph from start_node to end_node
// containing a list of path sorted by size
typedef struct s_flow
{
	t_dlist			*l_path;
	int				max_flow;
	int				nb_step;
	int				nb_prev;
	unsigned int	ants_distrub;
	unsigned int	ants_left;
	unsigned int	path_necessary;
}	t_flow;

// Prototypes

short	convert_data_graph(t_data *data, t_graph *graph);

// Utils for graph construction
short	create_node_out(t_node *node);
short	find_nodes(t_edge *edge, t_graph *graph, t_node **first_node,
			t_node **second_node);
t_node	*find_opposite_node(t_link *link, t_node *tail);
t_node	*convert_vertex_to_node(char *name);
void	reset_graph(t_graph *graph);
void	free_graph(t_graph *graph);
void	erase_node(t_node *node);
short	check_link_already_exist(t_graph *graph, t_node *node1, t_node *node2);
short	create_unique_room_link(t_graph *graph, t_node *node1, t_node *node2);

// Utils for t_flow
t_flow	*init_tflow(void);
void	free_tflow(t_flow *tflow);
short	tflow_insert_path(t_flow *tflow, t_path *path);
void	free_path(t_path *path);
short	path_insert(t_path *path, t_node *node);
t_path	*free_ret_path(t_path *path);

// utils or distrib ants in paths
bool	set_roolback(t_flow *flow, t_dlist *cursor, t_path *current);
void	resize_capacity(t_flow *flow, t_dlist *cursor, t_path *current);
int		get_nb_laps(t_flow *flow);
void	distib_in_path(t_flow *flow, unsigned int nb_ants);

#endif
