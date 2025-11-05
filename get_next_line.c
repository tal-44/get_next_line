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
	size_t			len;
	unsigned char	*dest;

	i = 0;
	len = 0;
	while (src[i])
		len++;
	dest = (unsigned char *)malloc((len + 1) * sizeof(char));
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
	char	*temp;
	char	*rest;

	i = 0;
	while (line[i] != '\n')
		i++;
	temp = (char *)malloc(++i * sizeof(char *));
	ft_strlcpy(temp, line, i);
	temp[i] = '\n';
	temp[i + 1] = '\0';
	if (line[i + 1])
	{
		rest = (char *)malloc(i * sizeof(char *));
		rest = ft_strdup(line + i);
	}
	else
		rest = NULL;
	free(current->line);
	current->line = rest;
	return (temp);
}

// considerar que hacer cuando acaba el archivo
static char	*ft_read_line(int fd, char **line, char *buffer, size_t *bytes_read)
{
	char	*temp;

	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[*bytes_read] = '\0';
	temp = ft_strjoin(*line, buffer);
	free(*line);
	*line = temp;
	// if (ft_strchr(buffer, '\n') || ())
	if (ft_strchr(buffer, '\n'))
		return (buffer);
	return (ft_read_line(fd, line, buffer, bytes_read));
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*current;
	char			buffer[BUFFER_SIZE + 1];
	size_t			bytes_read;
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
	if (line && ft_strchr(line, '\n'))
		return (ft_extract_line(line, current));
	else if (line)
	{
		line = ft_strjoin(current->line, ft_read_line(fd, &line, buffer,
					&bytes_read));
		return (ft_extract_line(line, current));
	}
	else
	{
		line = ft_read_line(fd, &line, buffer, &bytes_read);
		return (ft_extract_line(line, current));
	}
}
