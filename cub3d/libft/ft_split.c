/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 00:31:11 by tjmari            #+#    #+#             */
/*   Updated: 2020/01/31 20:57:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	*wordnext(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

static int	wordlen(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	myfree(char **output, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(output[i]);
		i++;
	}
	free(output);
}

char		**ft_split(char const *s, char c)
{
	char	**output;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = wordcount(s, c);
	if (!(output = (char **)malloc((words + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		s = wordnext(s, c);
		if (!(output[i] = ft_substr(s, 0, wordlen(s, c))))
		{
			myfree(output, i);
			return (NULL);
		}
		i++;
		s += wordlen(s, c);
	}
	output[words] = NULL;
	return (output);
}
