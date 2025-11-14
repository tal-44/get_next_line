/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/14 13:17:41 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_frees(char **stash, int fd, char *line, char *temp)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	if (stash && stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
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

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;
	char		*temp;
	char		*buffer;
	int			bytes;
	char		*newline_pos;
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stash[fd])
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (ft_frees(NULL, 0, NULL, buffer));
		buffer[bytes] = '\0';
		stash[fd] = ft_strdup(buffer);
		if (!stash[fd])
			return (ft_frees(NULL, 0, NULL, buffer));
	}
	while (!ft_strchr(stash[fd], '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_frees(stash, fd, NULL, buffer));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash[fd], buffer);
		if (!temp)
			return (ft_frees(stash, fd, NULL, buffer));
		free(stash[fd]);
		stash[fd] = temp;
	}
	if (!stash[fd] || stash[fd][0] == '\0')
		return (ft_frees(stash, fd, NULL, buffer));
	newline_pos = ft_strchr(stash[fd], '\n');
	if (newline_pos)
	{
		line_len = newline_pos - stash[fd] + 1;
		line = ft_substr(stash[fd], 0, line_len);
		if (!line)
			return (ft_frees(stash, fd, NULL, buffer));
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
			return (ft_frees(stash, fd, line, buffer));
		free(stash[fd]);
		stash[fd] = temp;
	}
	else
	{
		line = ft_strdup(stash[fd]);
		if (!line)
			return (ft_frees(stash, fd, NULL, buffer));
		free(stash[fd]);
		stash[fd] = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (line);
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
	line = get_next_line(fd);
	printf("[%s]", line);
	line = get_next_line(fd);
	printf("[%s]", line);
	free(line);
	if (fd >= 0)
		close(fd);
	return (0);
}
*/