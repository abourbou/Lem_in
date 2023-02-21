#include "../../include/lib.h"

bool	is_comment(char *line)
{
	if (line[0] != '#')
		return false;
	if (ft_strlen(line) == 1)
		return true;
	else if (line[1] == '#')
		return false;
	return (true);
}

bool	is_vertex(char *line)
{
	char	**arg;
	int		nb_args;

	arg = ft_split(line, ' ');
	nb_args = ft_substrlen(arg);
	if (nb_args != 3)
	{
		wrfree_parsing(arg);
		return (false);
	}
	wrfree_parsing(arg);
	return (true);
}

bool	is_edge(char *line)
{
	char	**arg;
	int		nb_args;

	arg = ft_split(line, ' ');
	nb_args = ft_substrlen(arg);
	if (nb_args != 1)
	{
		wrfree_parsing(arg);
		return (false);
	}
	wrfree_parsing(arg);
	arg = ft_split(line, '-');
	nb_args = ft_substrlen(arg);
	if (nb_args != 2)
	{
		wrfree_parsing(arg);
		return (false);
	}
	wrfree_parsing(arg);
	return (true);
}

bool	is_cmd(char *line)
{
	if (ft_strcmp(line, "##start") == 0 ||
		ft_strcmp(line, "##end") == 0)
	{
		return (true);
	}
	return (false);
}
