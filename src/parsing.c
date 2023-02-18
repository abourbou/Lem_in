#include "../include/lib.h"

bool	pars_args(t_data *data)
{
	lstadd_back_room(&data->start_room, lstnew_room("Coucou", 0, 1));
	lstadd_back_room(&data->start_room, lstnew_room("Hello", 1, 2));
	return EXIT_SUCCESS;
}
