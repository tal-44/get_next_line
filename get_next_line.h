
# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

static typedef struct s_list
{
    int fd;
    char *line;
    struct s_list *next;
}                       t_list;

char *get_next_line(int fd);
char *ft_strchr(const char *s, int c);
t_list *ft_lstnew(int fd);
t_list *ft_lstadd_back(t_list **lst, t_list *new);
char *ft_strjoin(char const *s1, char const *s2);

# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif