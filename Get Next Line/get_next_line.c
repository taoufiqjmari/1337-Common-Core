/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:24:01 by tjmari            #+#    #+#             */
/*   Updated: 2020/02/22 13:08:58 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_return(char *s, int i)
{
	free(s);
	s = NULL;
	return (i);
}

int	gnl_put(char **s, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i] == '\n')
	{
		*line = ft_substr(*s, 0, i);
		temp = ft_substr(*s, i + 1, ft_strlen(*s));
		free(*s);
		*s = temp;
		return (1);
	}
	else
	{
		*line = ft_substr(*s, 0, ft_strlen(*s));
		free(*s);
		*s = NULL;
		return (0);
	}
}

int	gnl_read(int fd, char **s, char **line, int i)
{
	char	*s2;
	char	*temp;

	if (!(s2 = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((i = read(fd, s2, BUFFER_SIZE)) > 0)
	{
		s2[i] = '\0';
		if (!s[fd])
			s[fd] = ft_substr("", 0, 0);
		temp = ft_strjoin(s[fd], s2);
		free(s[fd]);
		s[fd] = temp;
		if (ft_strchr(s[fd], '\n'))
			return (gnl_return(s2, gnl_put(&s[fd], line)));
	}
	if (i == -1)
		return (gnl_return(s2, i));
	else if (!s[fd] && i == 0)
	{
		*line = ft_substr("", 0, 0);
		return (gnl_return(s2, i));
	}
	else
		return (gnl_return(s2, gnl_put(&s[fd], line)));
}

int	get_next_line(int fd, char **line)
{
	static char	*keep[FD_LIMIT];

	if (fd < 0 || fd > FD_LIMIT || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (keep[fd] && ft_strchr(keep[fd], '\n'))
		return (gnl_put(&keep[fd], line));
	else
		return (gnl_read(fd, keep, line, 0));
}
