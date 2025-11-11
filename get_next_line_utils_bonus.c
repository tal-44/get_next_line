/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:51:53 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/07 10:51:56 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *str;
	size_t i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (str = ft_strdup(""));
	if (len > ft_strlen(s) - start)
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	size_t len1;
	size_t len2;

	len1 = 0;
	while (s1 && s1[len1])
		len1++;
	len2 = 0;
	while (s2 && s2[len2])
		len2++;
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len1 + 1);
	else
		str[0] = '\0';
	if (s2)
		ft_strlcpy(str + len1, s2, len2 + 1);
	else
		str[len1] = '\0';
	return (str);
}

char *ft_strchr(const char *s, int c)
{
	size_t i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
