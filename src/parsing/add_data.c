#include "../../include/lib.h"

int	add_vertex(t_data *data, char *line)
{
	char		**arg;
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

int	add_edge(t_data *data, char *line)
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

// int	process_basic_line(t_data *data, char **map, int *index)
// {
// 	char	**arg;
// 	int		room_or_link;

// 	arg = ft_split(map[*index], ' ');
// 	room_or_link = ft_substrlen(arg);
// 	if (room_or_link == 3)
// 	{
// 		if (add_vertex(data, map[*index]))
// 			return (EXIT_FAILURE);
// 	}
// 	else if (room_or_link == 1)
// 	{
// 		if (add_edge(data, map[*index]))
// 			return (EXIT_FAILURE);
// 	}
// 	else if (map[*index][0] != '#'){
// 		printf("test line = %s | size = %d\n", map[*index], room_or_link);
// 		return (print_error("Error : one line is incorrect.\n"));
// 	}
// 	return (EXIT_SUCCESS);
// }

process_line(int* step, line, start, end, data)
{
    if ((start || end) && step != 1)
        return EXIT_FAILURE;
    if (step == 0)
        process_nbr_ant();
    if (step == 1)
        process_room();
    if (step == 2)
        process_link();
}

parse_line()
{
    int isStart; // previous line was ##start
    int isEnd;   // previous line was ##end
    int step; //0 nbr_ant 1 room 2 edge

    while(map)
    {
        if (command)
            process_command();
        if (comment)
            continue;
        process_command(&step, line);
    }
}
