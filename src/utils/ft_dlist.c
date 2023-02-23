
#include "lib.h"

t_dlist *dlist_new(void *content)
{
    t_dlist *new = malloc(sizeof(t_dlist));

    new->content = content;
    new->next = 0;
    new->prev = 0;
    return (new);
}

void dlist_pushfront(t_dlist **start, t_dlist *new_elem)
{
	if (!start)
		return;
	if (!*start)
	{
		*start = new_elem;
		return;
	}
	new_elem->next = *start;
	(*start)->prev = new_elem;
	*start = new_elem;
}

void dlist_pushback(t_dlist **start, t_dlist *new_elem)
{
    t_dlist *current;

    if (!start)
        return;
    new_elem->prev = 0;
    new_elem->next = 0;
    if (!*start)
    {
        *start = new_elem;
        return;
    }

    current = *start;
    while (current->next)
        current = current->next;
    current->next = new_elem;
    new_elem->prev = current;
}

void dlist_addafter(t_dlist *current_elem, t_dlist *new_elem)
{
    t_dlist *next_elem;

    if (!current_elem || !new_elem)
        return;
    next_elem = current_elem->next;
    current_elem->next = new_elem;

    new_elem->prev = current_elem;
    new_elem->next = next_elem;

    if (next_elem)
        next_elem->prev = new_elem;
}
