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

bool	process_line(t_data *data, char **map, int *index)
{
	if (ft_strcmp(map[*index], "##start") == 0 ||
		ft_strcmp(map[*index], "##end") == 0)
	{
		if (process_command(data, map, index))
			return (EXIT_FAILURE);
	}
	else if (map[*index][0] == '#')
		return (EXIT_SUCCESS);
	else if (process_basic_line(data, map, index))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
