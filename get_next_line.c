
#include "get_next_line.h"

static char *ft_extract_line(char **line, t_list *current)
{
    char    *temp;

}

// considerar que hacer cuando acaba el archivo
static char *ft_read_line(int fd, char **line, t_list *current, char *buffer, size_t *bytes_read)
{
    char *temp;

    *bytes_read = read(fd, buffer, BUFFER_SIZE);
    buffer[*bytes_read] = '\0';
    temp = ft_strjoin(*line, buffer);
    free(*line);
    *line = temp;
    if (ft_strchr(buffer, '\n'))
        return ft_extract_line(line, current);
    return ft_read_line(fd, line, current, buffer, bytes_read);
}

char *get_next_line(int fd)
{
    static t_list *list;
    t_list *current;
    char buffer[BUFFER_SIZE + 1];
    size_t bytes_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    current = list;
    line = NULL;
    while (current)
    {
        if (current->fd == (char *)(size_t)fd)
            break;
        current = current->next;
    }
    if (!current)
    {
        current = ft_lstnew((char *)(size_t)fd);
        if (!current)
            return NULL;
        ft_lstadd_back(&list, current);
    }
    else if (current->line)
    {
        line = current->line;
        current->line = NULL;
    }
    if (line && ft_strchr(line, '\n'))
        return ft_extract_line(&line, current);
    return ft_read_line(fd, &line, current, buffer, &bytes_read);    
}