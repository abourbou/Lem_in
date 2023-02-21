#include "../include/lib.h"

void	init_data(t_data *data)
{
	data->numb_ants = 0;
	data->start_vertex = NULL;
	data->end_vertex = NULL;
	data->list_vertex = NULL;
	data->list_edge = NULL;
}

void free_and_exit()
{
	wrdestroy();
}

// int	check_arg(int ac, char **av)
// {
// 	printf("test ac = %d\n", ac);
// 	if (ac < 2 || ac > 3)
// 		return (print_error("Error : numbers of argument not valide\n"));
// 	if (ac == 3)
// 		print_error("fichier\n");
// 	if (ac == 2)
// 		print_error("entrer standart\n");
// 	return 0;
// }

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data);
	// if (check_arg(ac, av))
	// 	return (EXIT_FAILURE);
	if(pars_args(&data))
		return (EXIT_FAILURE);

	printf("start vertex = vertex : %s | cord x : %d | cord y : %d\n", data.start_vertex->name, data.start_vertex->cord_x, data.start_vertex->cord_y);
	printf("end vertex = vertex : %s | cord x : %d | cord y : %d\n\n", data.end_vertex->name, data.end_vertex->cord_x, data.end_vertex->cord_y);


	printf("list vertex :\n");
	for (t_vertex *cursor = data.list_vertex; cursor; cursor = cursor->next)
	{
		printf("name of vertex : %s | cord x : %d | cord y : %d\n", cursor->name, cursor->cord_x, cursor->cord_y);
	}

	printf("\nlist edge :\n");
	for (t_edge *cursor = data.list_edge; cursor; cursor = cursor->next)
	{
		printf("edge 1 : %s | edge 2 : %s | direction x : %d\n", cursor->vertex1, cursor->vertex2, cursor->direction);
	}
	free_and_exit();
	return 0;
}
