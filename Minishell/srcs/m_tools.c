/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 17:18:56 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 13:22:38 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	itis(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '<' || s[i] == '>')
		return (1);
	else if (s[i] == ';')
		return (2);
	else if (s[i] == '|')
		return (3);
	else if (!s[i])
		return (-1);
	else
		return (0);
}

void	nfree(void *s)
{
	if (s)
	{
		free (s);
		s = NULL;
	}
}

int	same(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	**doublefree(char **ptr)
{
	int	i;

	if (ptr != NULL)
	{
		i = doublecount(ptr);
		while (i >= 0)
		{
			free(ptr[i]);
			i--;
		}
		free(ptr);
	}
	ptr = NULL;
	return (NULL);
}

int	doublecount(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}
