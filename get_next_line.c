/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/10 15:56:57 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *ft_frees(char **buffer, char *line, char *temp)
{
	if (line)
		free(line);
	if (temp)
		free(temp);
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

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
			return (free(line), NULL);
		ft_strlcpy(temp, line, i + 2);
		rest = ft_strdup(line + i + 1);
		free(line);
		if (!rest)
			return (free(temp), NULL);
		if (buffer && *buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = rest;
		return (temp);
	}
	else
	{
		if (buffer && *buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
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
			break;
		buffer[bytes_read] = '\0';
		temp_line = ft_strjoin(line, buffer);
		if (!temp_line)
			return (free(line), NULL);
		if (line)
			free(line);
		line = temp_line;
		if (ft_strchr(line, '\n'))
			break;
	}
	if (bytes_read == 0 && (!line || *line == '\0'))
		return (free(line), NULL);
	/*	temp_line = line;
		line = ft_strdup(temp_line);
		return (free(temp_line), line);
	*/
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			had_data;
	char		*to_add;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	had_data = 0;
	if (!buffer)
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	else
	{
		line = ft_strdup(buffer);
		if (!line)
			return (ft_frees(&buffer, NULL, NULL));
		had_data = (line && line[0] != '\0');
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
		{
			free(line);
			return (NULL);
		}
		buffer[0] = '\0';
	}
	if (ft_strchr(line, '\n'))
		return (ft_extract_line(line, &buffer));
	else if (had_data)
	{
		to_add = ft_read_line(fd, NULL, buffer);
		if (!to_add)
			return (ft_frees(&buffer, line, NULL));
		new_line = ft_strjoin(line, to_add);
		ft_frees(NULL, line, to_add);
		if (!new_line)
			return (ft_frees(&buffer, NULL, NULL));
		line = new_line;
		return (ft_extract_line(line, &buffer));
	}
	else
	{
		line = ft_read_line(fd, line, buffer);
		if (!line)
			return (ft_frees(&buffer, NULL, NULL));
		return (ft_extract_line(line, &buffer));
	}
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
		i++;
	}
	if (fd >= 0)
		close(fd);
	return (0);
}
*/