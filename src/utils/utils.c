#include "../../include/lib.h"

int	ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return 0;
	while (str[i])
		i++;
	return (i);
}

int	print_error(char *strError)
{
	return(write(2, strError, ft_strlen(strError)));
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

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	p = *alst;
	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else if (p)
	{
		while (p->next)
			p = p->next;
		p->next = new;
	}
}
