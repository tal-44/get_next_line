
#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_list *list;
    t_list *current;
    char buffer[BUFFER_SIZE + 1];
    size_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    current = list;
    while (current)
    {
        if (current->fd == (char *)(size_t)fd)
            break;
        current = current->next;
    }
}