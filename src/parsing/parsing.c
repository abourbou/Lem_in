#include "../../include/lib.h"

static char	**read_stdin()
{
	char	*line;
	char	*ret = NULL;
	char	**map = NULL;

	while (get_next_line(0, &line))
		ret = ft_strjoin_sp(ret, line);
	map = ft_split(ret, '\n');
	return map;
}

static bool	first_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	skip_space_i(line, &i);
	data->numb_ants = atoi_numb(line, &i);
	if (check_space_end(line, &i))
		return ("Error : number of ants is in incorrect format.\n");
	if (data->numb_ants == 0)
		return ("Error : [numbers of ants] cant be 0.\n");
	return (EXIT_SUCCESS);
}

static int	parse_stdin(t_data *data, char **map)
{
	int	i;

	i = 0;
	if (first_line(data, map[i]))
		return (EXIT_FAILURE);
	i++;
	while (map[i])
	{
		if (process_line(data, map, &i))
			return (EXIT_FAILURE);
		if (map[i])
			i++;
	}
	puts("end of map\n");
	return 0;
}

bool	pars_args(t_data *data)
{
	char	**map = NULL;

	lstadd_back_room(&data->start_room, lstnew_room("Coucou", 0, 1));
	map = read_stdin();
	if (map == NULL)
		return (print_error("Error : empty entry\n"));
	if (parse_stdin(data, map))
		return (EXIT_FAILURE);
	(void)data;
	return EXIT_SUCCESS;
}
