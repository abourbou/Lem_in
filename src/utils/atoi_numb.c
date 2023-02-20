/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_numb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:06:14 by sbaranes          #+#    #+#             */
/*   Updated: 2021/03/24 10:19:02 by sbaranes         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib.h"

void	skip_space_i(char *str, int *i)
{
	while (str[*i] == ' ')
	{
		*i += 1;
	}
}

int	check_space_end(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] != ' ')
			return (1);
		*i += 1;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	while ((s1[x] && s2[x]))
	{
		if (s1[x] != s2[x])
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		x++;
	}
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

short	ft_isnumber(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	atoi_numb(char *str, int *i)
{
	int		result;

	result = 0;
	while (ft_isnumber(str[*i]))
	{
		result = result * 10 + (str[*i] - '0');
		*i += 1;
	}
	return (result);
}
