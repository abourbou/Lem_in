/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:59:59 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 11:00:49 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	free_data(t_data *data)
{
	if (data->list_edge)
		lstclear_edge(data);
	if (data->list_map)
		lstclear_map(data);
	if (data->list_vertex)
		lstclear_vertex(data);
	if (data->dico_vertex)
		free_dico_vertex(data->dico_vertex);
}

void	free_exit(t_data *data, char *msg_error, char **tab)
{
	if (tab)
		free_tab(tab);
	free_data(data);
	if (msg_error != NULL)
		exit(write(2, msg_error, ft_strlen(msg_error)));
	else
		exit(EXIT_FAILURE);
}

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	dest = malloc(count * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, (count * size));
	return (dest);
}
