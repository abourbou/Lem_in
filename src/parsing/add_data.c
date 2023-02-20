#include "../../include/lib.h"

static int	add_room(t_data *data, char *line)
{
	char	**arg;
	t_room	*new_room;

	arg = ft_split(map[*index], ' ');
	if (arg[0][0] == 'L' || arg[0][0] == '#')
		return (print_error("Error : room name cant start by # or 'L'\n"));
	if (is_interger(arg[1]))
		return (EXIT_FAILURE);
	if (is_interger(arg[2]))
		return (EXIT_FAILURE);
	new_room = lstnew_room(arg[0], arg[1], arg[2]);
	lstadd_back_room(&data->start_room, new_room);
	return (EXIT_SUCCESS);
}

static int	add_link(t_data *data, char *line)
{
	return (EXIT_SUCCESS);
}

int	process_basic_line(t_data *data, char **map, int *index)
{
	char	**arg;
	int		room_or_link;

	room_or_link = ft_substrlen(arg);
	arg = ft_split(map[*index], ' ');
	if (room_or_link == 3)
		if (add_room(data, map[*index]))
			return (EXIT_FAILURE);
	else if (room_or_link == 1)
		if (add_link(data, map[*index]))
			return (EXIT_FAILURE);
	else
		return (print_error("Error : one line is incorrect.\n"));
	return (EXIT_SUCCESS);
}
