#include "../../include/lib.h"

int is_interger(char *line)
{
	int	i;

	i = 0 ;
	while (line[i])
	{
		if (ft_isnumber(line[i]) == 0)
			return (print_error("Error : coordinates need always be integers.\n"));
		i++;
	}
	return EXIT_SUCCESS;
}

static int	process_command(t_data *data, char **map, int *index)
{
	bool		start;
	char		**arg;
	t_vertex	*new_vertex;

	start = false;
	if (ft_strcmp(map[*index], "##start") == 0)
		start = true;
	*index += 1;
	arg = ft_split(map[*index], ' ');
	if (ft_substrlen(arg) != 3)
		return (print_error("Error : bad number of argument in line\n"));
	if (arg[0][0] == 'L' || arg[0][0] == '#')
		return (print_error("Error : room name cant start by # or 'L'\n"));
	if (is_interger(arg[1]))
		return (EXIT_FAILURE);
	if (is_interger(arg[2]))
		return (EXIT_FAILURE);
	new_vertex = lstnew_vertex(arg[0], atoi(arg[1]), atoi(arg[2]));
	lstadd_back_vertex(&data->list_vertex, new_vertex);
	if (start)
		data->start_vertex = new_vertex;
	else
		data->end_vertex = new_vertex;
	return (EXIT_SUCCESS);
}

int	process_vertex(t_data *data, char **map, int *index)
{
	if (is_cmd(map[*index]))
	{
		if (process_command(data, map, index))
			return (EXIT_FAILURE);
	}
	else if (is_comment(map[*index]))
		*index += 1;
	if (map[*index])
	{
		if (is_vertex(map[*index]))
			if (add_vertex(data, map[*index]))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_edge(t_data *data, char **map, int *index)
{
	if (is_comment(map[*index]))
		*index += 1;
	if (map[*index])
	{
		if (is_edge(map[*index]))
			if (add_edge(data, map[*index]))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	process_line(t_data *data, char **map, int *index)
{
	while (map[*index] && (is_cmd(map[*index]) ||
		is_comment(map[*index]) || is_vertex(map[*index])))
	{
		printf("DEBUG in while vertex | line = %s\n", map[*index]);
		printf("cmd ? %d | comment ? %d | vertex ? %d\n", is_cmd(map[*index]) , is_comment(map[*index]) , is_vertex(map[*index]));
		process_vertex(data, map, index);
		*index += 1;
	}
	while (map[*index] && (is_comment(map[*index]) ||
		is_edge(map[*index])))
	{
		printf("DEBUG in while edge | line = %s\n", map[*index]);
		printf("comment ? %d | edge ? %d\n", is_comment(map[*index]) , is_edge(map[*index]));

		process_edge(data, map, index);
		*index += 1;
	}
}
