/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/07 10:39:37 by jmiguele         ###   ########.fr       */
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

static char	*ft_extract_line(char *line, char **buffer)
{
	size_t	i;
	char	*rest;
	char	*temp;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
	{
		temp = malloc(i + 2);
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, line, i + 2);
		rest = ft_strdup(line + i + 1);
		free(line);
		line = temp;
		free(*buffer);
		*buffer = rest;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
		rest = NULL;
	}
	return (line);
}

static char	*ft_read_line(int fd, char *line, char *buffer)
{
	char	*temp_line;
	ssize_t	bytes_read;

	bytes_read = -1;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp_line = ft_strjoin(line, buffer);
		if (!temp_line)
			return (free(line), NULL);
		free(line);
		line = ft_strdup(temp_line);
		free(temp_line);
		if (ft_strchr(line, '\n'))
			break ;
	}
	if (bytes_read == 0 && (!line || *line == '\0'))
		return (free(line), NULL);
	temp_line = line;
	line = ft_strdup(temp_line);
	return (free(temp_line), line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (!buffer[fd])
	{
		buffer[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		buffer[fd][0] = '\0';
	}
	else
	{
		line = ft_strdup(buffer[fd]);
		if (!line)
			return (free(line), NULL);
		free(buffer[fd]);
		buffer[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer[fd])
			return (free(line), NULL);
		buffer[fd][0] = '0';
	}
	if (ft_strchr(line, '\n'))
		return (ft_extract_line(line, &buffer[fd]));
	else if (buffer[fd][0] != '\0')
	{
		line = ft_strjoin(line, ft_read_line(fd, NULL, buffer[fd]));
		if (!line)
			return (free(line), NULL);
		return (ft_extract_line(line, &buffer[fd]));
	}
	else
	{
		line = ft_read_line(fd, line, buffer[fd]);
		if (!line)
			return (free(line), NULL);
		return (ft_extract_line(line, &buffer[fd]));
	}
}
/*
int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	i++;
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line)
	{
		printf("[1]\n%s\n", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("[2]\n%s\n", line);
		free(line);
	}
	if (fd >= 0)
		close(fd);
	return (0);
}
*/