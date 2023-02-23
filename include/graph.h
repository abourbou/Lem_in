/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:38:52 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:30:52 by abourbou         ###   ########lyon.fr   */
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
	unsigned int	dist_source;
	int				ant_nb;
}	t_node;

/**
 * Link structure containing:
 * - terminal : node where it goes
 * - flow : status of the link
 *   (0 = blocked, 1 = available, 2 = used)
*/
typedef struct s_link
{
	t_node	*terminal;
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
	t_dlist	*lnode;
	t_node	*source;
	t_node	*sink;
}	t_graph;

typedef struct s_path
{
	t_node			*arr_node;
	unsigned int	length;
}	t_path;

// flow of a graph from source to sink
// containing a list of path sorted by size
typedef struct s_flow
{
	t_dlist	*t_path;
}	t_flow;

// Prototypes
short	convert_data_graph(t_data *data, t_graph *graph);

// Utils for graph construction
short	create_link(t_node *node1, t_node *node2);
short	find_nodes(t_edge *edge, t_graph *graph, t_node **first_node,
			t_node **second_node);
t_node	*convert_vertex_to_node(t_vertex *vertex);
void	free_node(t_node *node);
void	free_graph(t_graph *graph);
void	erase_node(t_node *node);
short	check_edge_already_exist(t_node *node1, t_node *node2);
#endif