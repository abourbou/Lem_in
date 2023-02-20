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

typedef struct s_room t_room; // vertex - room || edge pour les lien
typedef struct s_random t_random;

struct s_room
{
	char	*name;
	int		cord_x;
	int		cord_y;
	t_room	*next;
	t_room	*prev;
};

struct s_random
{
	char		*name;
	int			direction;
	t_random	*next;
	t_random	*prev;
};

typedef struct s_data
{
	int		numb_ants;
	t_room	*list_room;
	t_room	*start_room;
	t_room	*end_room;
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
short	ft_isnumber(int c);
bool	pars_args(t_data *data);
bool	process_line(t_data *data, char **map, int *index);
int		ft_strlen(char *str);
int		print_error(char *strError);
int		atoi_numb(char *str, int *i);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		check_space_end(char *str, size_t *i);
void	skip_space_i(char *str, int *i);
int		ft_substrlen(char **str);
char	*ft_strjoin_sp(char *s1, char *s2);

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
t_room	*lstnew_room(char *name, int cord_x, int cord_y);
t_room	*lstlast_room(t_room *lstt);
void	lstadd_front_room(t_room **alst, t_room *new);
void	lstadd_back_room(t_room **alst, t_room *new);

/*
** Function for random list
*/
t_random	*lstnew_random(char *name);
t_random	*lstlast_random(t_random *lstt);
void	lstadd_front_random(t_random **alst, t_random *new);
void	lstadd_back_random(t_random **alst, t_random *new);

/*
** Function for save pointer and free them easy
*/
void	*wrmalloc(unsigned long size);
int		wrfree(void *ptr);
void	wrdestroy(void);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif
