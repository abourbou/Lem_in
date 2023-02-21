#include "../../include/lib.h"

static int	add_vertex(t_data *data, char *line)
{
	char	**arg;
	t_vertex	*new_vertex;

	arg = ft_split(line, ' ');
	if (arg[0][0] == 'L' || arg[0][0] == '#')
		return (print_error("Error : room name cant start by # or 'L'.\n"));
	if (is_interger(arg[1]))
		return (EXIT_FAILURE);
	if (is_interger(arg[2]))
		return (EXIT_FAILURE);
	new_vertex = lstnew_vertex(arg[0], atoi(arg[1]), atoi(arg[2]));
	lstadd_back_vertex(&data->list_vertex, new_vertex);
	return (EXIT_SUCCESS);
}

static int	add_link(t_data *data, char *line)
{
	char	**arg;
	t_edge	*new_edge;

	arg = ft_split(line, '-');
	if (ft_substrlen(arg) != 2)
		return (print_error("Error : line link bad format.\n"));
	if ((arg[0][0] == 'L' || arg[0][0] == '#') ||
		(arg[1][0] == 'L' || arg[1][0] == '#'))
		return (print_error("Error : room name cant start by # or 'L'.\n"));
	new_edge = lstnew_edge(arg[0], arg[1], 0);
	lstadd_back_edge(&data->list_edge, new_edge);
	return (EXIT_SUCCESS);
}

int	process_basic_line(t_data *data, char **map, int *index)
{
	char	**arg;
	int		room_or_link;

	arg = ft_split(map[*index], ' ');
	room_or_link = ft_substrlen(arg);
	//! Check first room then link, not at the same time!
	if (room_or_link == 3)
	{
		if (add_vertex(data, map[*index]))
			return (EXIT_FAILURE);
	}
	else if (room_or_link == 1)
	{
		if (add_link(data, map[*index]))
			return (EXIT_FAILURE);
	}
	else
		return (print_error("Error : one line is incorrect.\n"));
	return (EXIT_SUCCESS);
}
