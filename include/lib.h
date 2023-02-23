/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:53:02 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:30:54 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
// TODO erase time at the end
# include <time.h>

# define BUFFER_SIZE 42
# define COM 0
# define CMD 1
# define VERTEX 2
# define EDGE 3
# define UNKNOWN 4

/*
******************** Struct ********************
*/

typedef struct s_vertex
{
	char			*name;
	int				cord_x;
	int				cord_y;
	struct s_vertex	*next;
	struct s_vertex	*last;
}	t_vertex;

typedef struct s_edge
{
	char			*vertex1;
	char			*vertex2;
	int				direction;
	struct s_edge	*last;
	struct s_edge	*next;
}	t_edge;

typedef struct s_map
{
	char			*line;
	struct s_map	*last;
	struct s_map	*next;
}	t_map;

typedef struct s_pars
{
	int		step;
	int		start;
	int		end;
}	t_pars;

typedef struct s_btnode
{
	char			*name;
	struct s_btnode	*left;
	struct s_btnode	*right;
}	t_btnode;

typedef struct s_data
{
	int			numb_ants;
	t_vertex	*list_vertex;
	t_btnode	*dico_vertex;
	t_vertex	*start_vertex;
	t_vertex	*end_vertex;
	t_edge		*list_edge;
	t_map		*list_map;
	t_pars		pars;
}	t_data;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

/*
******************** Function ********************
*/

void		free_data(t_data *data);
void		free_exit(t_data *data, char *msg_error, char **tab);
void		ft_putstrln(char *line);

/*
** Function for parsing
*/
void		parse_stdin(t_data *data);
bool		set_start_or_end(t_data *data, t_vertex *new_vertex, int code);

short		ft_isnumber(int c);
bool		pars_args(t_data *data);
int			define_line(char *line);
int			ft_strlen(char *str);
void		print_error(char *strError);
int			atoi_sp(char *str, int *i);
char		**ft_split(char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
int			check_space_end(char *str, int *i);
void		skip_space_i(char *str, int *i);
int			ft_substrlen(char **str);
// char		*ft_strjoin_sp(char *s1, char *s2);
void		free_tab(char **str);
int			is_interger(char *line);
char		*ft_strdup(char *src);

/*
** Function for get_next_line package
*/
int			get_next_line(int fd, char **line);
size_t		fh_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
size_t		fh_strcpy(char *dst, const char *src);
char		*fh_strjoin(char const *s1, char const *s2);
int			contains(char *str, char c);
void		*ft_calloc(size_t count, size_t size);

/*
** Function for vertex list
*/
t_vertex	*lstnew_vertex(char *name, int cord_x, int cord_y);
// t_vertex	*lstlast_vertex(t_vertex *lstt);
void		lstadd_back_vertex(t_vertex **alst, t_vertex *new);
void		lstclear_vertex(t_data *data);

/*
** Function for edge list
*/
t_edge		*lstnew_edge(char *vertex1, char *vertex2, int direction);
// t_edge		*lstlast_edge(t_edge *lstt);
void		lstadd_back_edge(t_edge **alst, t_edge *new);
void		lstclear_edge(t_data *data);

/*
** Function for map list
*/
t_map		*lstnew_map(char *line);
t_map		*lstlast_map(t_map *lstt);
void		lstadd_back_map(t_map **alst, t_map *new);
void		print_map(t_map *list_map);
void		lstclear_map(t_data *data);

/*
** Function for dico vertex node
*/
t_btnode	*new_vertex(char *name);
t_btnode	*add_node(t_btnode *node, char *name);
bool		is_exist(t_btnode *node, char *name);
void		free_dico_vertex(t_btnode *node);

int			print_error_return(char *msg, int signal);
void		free_if_not_empty(void *ptr);

/**
 * Double linked functions
*/
t_dlist		*dlist_new(void *content);
void		dlist_pushfront(t_dlist **start, t_dlist *new_elem);
void		dlist_pushback(t_dlist **start, t_dlist *new_elem);
void		dlist_addafter(t_dlist *current_elem, t_dlist *new_elem);
void		dlist_erase(t_dlist **start, t_dlist *elem);
size_t		dlist_compt(t_dlist *list);

#endif
