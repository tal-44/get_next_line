
# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

static typedef struct s_list
{
    char *fd;
    char *line;
    struct s_list *next;
}                       t_list;

char *get_next_line(int fd);

# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif