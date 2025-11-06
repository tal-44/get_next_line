/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:51:50 by jmiguele          #+#    #+#             */
/*   Updated: 2025/11/06 10:12:44 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*line;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
char				*ft_strchr(const char *s, int c);
t_list				*ft_lstnew(int fd);
void				ft_lstadd_back(t_list **lst, t_list *new);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);

#endif