/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:48 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/15 20:07:06 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_frees(char **stash, char *temp)
{
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	if (stash)
	{
		free(*stash);
		*stash = NULL;
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

static void	ft_extract_line(char **stash, char **line)
{
	char	*newline_pos;
	size_t	line_len;
	char	*temp;

	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - *stash + 1;
		*line = ft_substr(*stash, 0, line_len);
		if (!*line)
		// return (ft_frees(stash, NULL));
		{
			ft_frees(stash, NULL);
			return ;
		}
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
		// return (ft_frees(stash, *line));
		{
			ft_frees(stash, *line);
			*line = NULL;
			return ;
		}
		free(*stash);
		*stash = temp;
		return ;
		// return (NULL);
	}
	*line = ft_strdup(*stash);
	ft_frees(stash, NULL);
}

int	ft_read_loop(char *buffer, char **stash, int fd)
{
	char	*temp;
	int		bytes;

	while (!ft_strchr(*stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_frees(stash, buffer), 1);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(*stash, buffer);
		if (!temp)
			return (ft_frees(stash, buffer), 1);
		free(*stash);
		*stash = temp;
	}
	ft_frees(NULL, buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stash)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (ft_frees(NULL, buffer));
		buffer[bytes] = '\0';
		stash = ft_strdup(buffer);
		if (!stash)
			return (ft_frees(NULL, buffer));
	}
	if (ft_read_loop(buffer, &stash, fd))
		return (NULL);
	if (!stash || stash[0] == '\0')
		return (ft_frees(&stash, NULL));
	ft_extract_line(&stash, &buffer);
	return (buffer);
}
