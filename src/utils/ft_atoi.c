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

int	atoi_numb(char *str, int *i)
{
	int	result;

	result = 0;
	while (ft_isnumber(str[*i]))
	{
		result = result * 10 + (str[*i] - '0');
		*i += 1;
	}
	return (result);
}

int	ft_substrlen(char **str)
{
	int i = 0;

	if (!*str)
		return 0;
	while (*str[i])
		i++;
	return (i);
}
