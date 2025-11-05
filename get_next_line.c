/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/05 12:58:55 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *src)
{
	size_t			i;
	unsigned char	*dest;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
		i++;
	dest = (unsigned char *)malloc((i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)(dest));
}

static char	*ft_extract_line(char *line, t_list *current)
{
	size_t	i;
	char	*temp_line;
	char	*rest;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
    if (line[i] == '\n')
	{
		temp_line = (char *)malloc(i + 2);
		if (!temp_line)
			return (NULL);
		ft_strlcpy(temp_line, line, i + 2);
		rest = ft_strdup(line + i + 1);
	}
	else
	{
		temp_line = ft_strdup(line);
		rest = NULL;
	}
	free(current->line);
	current->line = rest;
	return (temp_line);
}

static char	*ft_read_line(int fd, char *line, char *buffer, ssize_t *bytes_read)
{
    char    *temp_line;

	while (1)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read < 0)
            return (free(line), NULL);
		if (*bytes_read == 0)
			break;
		buffer[*bytes_read] = '\0';
		temp_line = ft_strjoin(line, buffer);
		if (!temp_line)
			return (free(line), NULL);
		free(line);
		line = temp_line;
		if (ft_strchr(line, '\n'))
			break;
	}
	if (*bytes_read == 0 && (!line || *line == '\0'))
        return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*current;
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			bytes_read = -1;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = list;
	line = NULL;
	while (current)
	{
		if (current->fd == fd)
			break ;
		current = current->next;
	}
	if (!current)
	{
		current = ft_lstnew(fd);
		if (!current)
			return (NULL);
		ft_lstadd_back(&list, current);
	}
	else if (current->line)
	{
		line = current->line;
		current->line = NULL;
	}
    buffer[0] = '\0';
	if (line && ft_strchr(line, '\n'))
		return (ft_extract_line(line, current));
	else if (line)
	{
		line = ft_read_line(fd, line, buffer, &bytes_read);
        if (!line)
            return (NULL);
		return (ft_extract_line(line, current));
	}
	else
	{
		line = ft_read_line(fd, line, buffer, &bytes_read);
		if (!line)
            return (NULL);
		return (ft_extract_line(line, current));
	}
}
