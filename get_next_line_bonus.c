/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/13 09:42:41 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_frees(char **buffer, int fd, char *line, char *temp)
{
	if (line)
		free(line);
	if (temp)
		free(temp);
	if (buffer && buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
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
	char		buffer[BUFFER_SIZE + 1];
	int			bytes;
	char		*newline_pos;
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	while (!ft_strchr(stash[fd], '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_frees(stash, fd, NULL, NULL));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash[fd], buffer);
		if (!temp)
			return (ft_frees(stash, fd, NULL, NULL));
		free(stash[fd]);
		stash[fd] = temp;
	}
	if (!stash[fd] || stash[fd][0] == '\0')
		return (ft_frees(stash, fd, NULL, NULL));
	newline_pos = ft_strchr(stash[fd], '\n');
	if (newline_pos)
	{
		line_len = newline_pos - stash[fd] + 1;
		line = ft_substr(stash[fd], 0, line_len);
		if (!line)
			return (ft_frees(stash, fd, NULL, NULL));
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
		{
			free(line);
			return (ft_frees(stash, fd, NULL, NULL));
		}
		free(stash[fd]);
		stash[fd] = temp;
	}
	else
	{
		line = ft_strdup(stash[fd]);
		if (!line)
			return (ft_frees(stash, fd, NULL, NULL));
		free(stash[fd]);
		stash[fd] = NULL;
	}
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
	//	fd = open(1, O_RDONLY);
	while (1)
	{
		line = get_next_line(1);
		printf("%s\n", line);
		free(line);
	}
	if (fd >= 0)
		close(fd);
	return (0);
}
*/