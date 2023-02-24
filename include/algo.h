/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:24:35 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/23 16:45:21 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "graph.h"
# include "queue.h"

short	check_path_exists(t_graph *graph);
void	erase_dead_end_nodes(t_graph *graph);
void	construct_level_graph(t_graph *graph);

#endif