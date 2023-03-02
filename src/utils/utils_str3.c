/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:24:04 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 14:29:50 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strconcat(char *str1, char *str2)
{
	size_t	len;
	char	*result;
	int		i;
	int		j;

	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	result = malloc(sizeof(char) * len);
	i = 0;
	while (str1[i])
	{
		result[i] = str1[i];
		++i;
	}
	j = 0;
	while (str2[j])
	{
		result[i + j] = str2[j];
		++j;
	}
	result[i + j] = 0;
	return (result);
}
