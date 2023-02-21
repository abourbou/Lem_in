#include "../../include/lib.h"

void	skip_space_i(char *str, int *i)
{
	while (str[*i] == ' ')
	{
		*i += 1;
	}
}

int	check_space_end(char *str, int *i)
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
	free(s2);
	return (str);
}
