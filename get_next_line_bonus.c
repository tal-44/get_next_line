/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/15 19:52:52 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_frees(char **stash, int fd, char *temp)
{
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

static void	*ft_extract_line(char *stash[1024], int fd, char **line)
{
	char	*newline_pos;
	size_t	line_len;
	char	*temp;

	newline_pos = ft_strchr(stash[fd], '\n');
	if (newline_pos)
	{
		line_len = newline_pos - stash[fd] + 1;
		*line = ft_substr(stash[fd], 0, line_len);
		if (!*line)
			return (ft_frees(stash, fd, NULL));
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
			return (ft_frees(stash, fd, *line));
		free(stash[fd]);
		stash[fd] = temp;
		return (NULL);
	}
	*line = ft_strdup(stash[fd]);
	return (ft_frees(stash, fd, NULL));
}

int	ft_read_loop(char *buffer, char **stash, int fd)
{
	char	*temp;
	int		bytes;

	while (!ft_strchr(stash[fd], '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_frees(stash, fd, buffer), 1);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash[fd], buffer);
		if (!temp)
			return (ft_frees(stash, fd, buffer), 1);
		free(stash[fd]);
		stash[fd] = temp;
	}
	ft_frees(NULL, 0, buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stash[fd])
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (ft_frees(NULL, 0, buffer));
		buffer[bytes] = '\0';
		stash[fd] = ft_strdup(buffer);
		if (!stash[fd])
			return (ft_frees(NULL, 0, buffer));
	}
	if (ft_read_loop(buffer, stash, fd))
		return (NULL);
	if (!stash[fd] || stash[fd][0] == '\0')
		return (ft_frees(stash, fd, NULL));
	ft_extract_line(stash, fd, &buffer);
	return (buffer);
}
