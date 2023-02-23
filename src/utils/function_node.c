#include "../../include/lib.h"

static t_node	*new_node(char *name)
{
	t_node	*new_node;

	new_node = ft_calloc(1 , sizeof(t_node));
	new_node->name = ft_strdup(name);
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

t_node	*add_node(t_node *node, char *name)
{
	if (node == NULL)
		return new_node(name);
	if (ft_strcmp(name, node->name) < 0)
		node->left = add_node(node->left, name);
	else if (ft_strcmp(name, node->name) > 0)
		node->right = add_node(node->right, name);
	return node;
}

bool	is_existe(t_node *node, char *name)
{
	int		som;

	if (node == NULL)
		return false;
	som = ft_strcmp(node->name, name);
	if (som == 0)
		return true;
	else if (som > 0)
		return is_existe(node->left, name);
	else
		return is_existe(node->right, name);
}

void	free_dico_vertex(t_node *node)
{
	if (node == NULL)
		return;
	free(node->name);
	free_dico_vertex(node->left);
	free_dico_vertex(node->right);
	free(node);
}
