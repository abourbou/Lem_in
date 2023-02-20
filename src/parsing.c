#include "../include/lib.h"

char	*ft_strjoin_sp(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	x;

	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	x = 0;
	if (s1)
		while (s1[++i])
			str[x++] = s1[i];
	str[x++] = '\n';
	i = -1;
	if (s2)
		while (s2[++i])
			str[x++] = s2[i];
	str[x] = '\0';
	free(s1);
	return (str);
}

char	**read_stdin()
{
	char	*line;
	char	*ret = NULL;
	char	**map = NULL;

	while (get_next_line(0, &line))
		ret = ft_strjoin_sp(ret, line);
	map = ft_split(ret, '\n');
	return map;
}

void	start_process_data(t_data *data, char **map, int *index)
{

}

bool	process_line(t_data *data, char **map, int *index)
{
	if (ft_strcmp(map[*index], "##start") == 0 ||
		ft_strcmp(map[*index], "##end") == 0)
		if (start_process_data(data, map, index))
			return (EXIT_FAILURE);
	else if (map[*index][0] == '#' && map[*index][1] != '#')
		*index += 1;
}

bool	first_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	skip_space_i(line, &i);
	while (line[i])
	{
		if (ft_isnumber(line[i]) == 0)
			return ("Error : bad format [numbers of ants] incorrect.\n");
		i++;
	}
	i = 0;
	data->numb_ants = atoi_numb(line, &i);
	if (check_space_end(line, &i))
		return ("Error : too mush args on first line.\n");
	if (data->numb_ants == 0)
		return ("Error : [numbers of ants] cant be 0.\n");
	return (EXIT_SUCCESS);
}

int	parse_stdin(t_data *data, char **map)
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
