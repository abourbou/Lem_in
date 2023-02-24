/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:59:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 10:59:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static bool	is_comment(char *line)
{
	if (line[0] == '#' && ft_strcmp(line, "##start")
		&& ft_strcmp(line, "##end"))
		return (true);
	return (false);
}

static bool	is_vertex(char *line)
{
	char	**arg;
	int		nb_args;

	arg = ft_split(line, ' ');
	nb_args = ft_substrlen(arg);
	if (nb_args != 3)
	{
		free_tab(arg);
		return (false);
	}
	free_tab(arg);
	return (true);
}

static bool	is_edge(char *line)
{
	char	**arg;
	int		nb_args;

	arg = ft_split(line, ' ');
	nb_args = ft_substrlen(arg);
	if (nb_args != 1)
	{
		free_tab(arg);
		return (false);
	}
	free_tab(arg);
	arg = ft_split(line, '-');
	nb_args = ft_substrlen(arg);
	if (nb_args != 2)
	{
		free_tab(arg);
		return (false);
	}
	free_tab(arg);
	return (true);
}

static bool	is_cmd(char *line)
{
	if (ft_strcmp(line, "##start") == 0
		|| ft_strcmp(line, "##end") == 0)
	{
		return (true);
	}
	return (false);
}

int	define_line(char *line)
{
	if (is_comment(line))
		return (COM);
	else if (is_cmd(line))
		return (CMD);
	else if (is_edge(line))
		return (EDGE);
	else if (is_vertex(line))
		return (VERTEX);
	return (UNKNOWN);
}
