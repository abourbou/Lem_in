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

int is_interger(char *line)
{
	int	i;

	i = 0 ;
	while (line[i])
	{
		if (ft_isnumber(line[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return EXIT_SUCCESS;
}
