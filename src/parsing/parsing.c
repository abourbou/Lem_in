#include "../../include/lib.h"

static void	print_free_map(t_data *data)
{
	t_map	*save;

	while (data->list_map)
	{
		save = data->list_map;
		ft_putstrln(data->list_map->line);
		free(data->list_map->line);
		data->list_map = data->list_map->next;
		free(save);
	}
	data->list_map = NULL;
}

static void	read_stdin(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			free_exit(data, "Error : empty line\n", NULL);
		}
		lstadd_back_map(&data->list_map, lstnew_map(line));
		free(line);
	}
	free(line);
}

bool	pars_args(t_data *data)
{
	read_stdin(data);
	parse_stdin(data);
	if (data->start_vertex == NULL)
		free_exit(data, "Error : Commande Start not found.\n", NULL);
	if (data->end_vertex == NULL)
		free_exit(data, "Error : Commande End not found.\n", NULL);
	print_free_map(data);
	return EXIT_SUCCESS;
}
