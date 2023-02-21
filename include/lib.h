#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

/*
******************** Struct ********************
*/

typedef struct s_vertex t_vertex; // vertex - room || edge pour les lien
typedef struct s_edge t_edge;

struct s_vertex
{
	char	*name;
	int		cord_x;
	int		cord_y;
	t_vertex	*next;
	t_vertex	*prev;
};

struct s_edge
{
	char		*vertex1;
	char		*vertex2;
	int			direction;
	t_edge	*next;
	t_edge	*prev;
};

typedef struct s_data
{
	int			numb_ants;
	t_vertex	*list_vertex;
	t_vertex	*start_vertex;
	t_vertex	*end_vertex;
	t_edge		*list_edge;
}t_data;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

/*
******************** Function ********************
*/

/*
** Function for parsing
*/
int	add_vertex(t_data *data, char *line);
int	add_edge(t_data *data, char *line);

short	ft_isnumber(int c);
bool	pars_args(t_data *data);
bool	process_line(t_data *data, char **map, int *index);
int		process_basic_line(t_data *data, char **map, int *index);
bool	is_comment(char *line);
bool	is_edge(char *line);
bool	is_vertex(char *line);
bool	is_cmd(char *line);
int		ft_strlen(char *str);
int		print_error(char *strError);
int		atoi_sp(char *str, int *i);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		check_space_end(char *str, int *i);
void	skip_space_i(char *str, int *i);
int		ft_substrlen(char **str);
char	*ft_strjoin_sp(char *s1, char *s2);
void	free_tab(char **str);
int		is_interger(char *line);
char	*ft_strdup(char *src);

/*
** Function for get_next_line package
*/
int		get_next_line(int fd, char **line);
size_t	fh_strlen(const char *s);
size_t	fh_strcpy(char *dst, const char *src);
char	*fh_strjoin(char const *s1, char const *s2);
int		contains(char *str, char c);
void	*ft_calloc(size_t count, size_t size);

/*
** Function for room list
*/
t_vertex	*lstnew_vertex(char *name, int cord_x, int cord_y);
t_vertex	*lstlast_vertex(t_vertex *lstt);
void		lstadd_front_vertex(t_vertex **alst, t_vertex *new);
void		lstadd_back_vertex(t_vertex **alst, t_vertex *new);

/*
** Function for random list
*/
t_edge	*lstnew_edge(char *vertex1, char *vertex2 , int direction);
t_edge	*lstlast_edge(t_edge *lstt);
void	lstadd_front_edge(t_edge **alst, t_edge *new);
void	lstadd_back_edge(t_edge **alst, t_edge *new);

/*
** Function for save pointer and free them easy
*/
void	*wrmalloc(unsigned long size);
void	*wrmalloc_parsing(unsigned long size);
int		wrfree(void *ptr);
void	wrdestroy(void);
void	wrdestroy_parsing(void);
int		wrfree_parsing(void *ptr);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif
