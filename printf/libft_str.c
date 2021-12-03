/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:42:41 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 15:28:02 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s2;

	if (!(s2 = (char *)malloc((len + 1) * sizeof(char))) || !s)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			s2[i] = s[start];
			start++;
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_strrev(char **str)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(*str);
	temp = (char *)malloc(len + 1);
	while (len > 0)
		temp[i++] = (*str)[--len];
	temp[i] = '\0';
	free(*str);
	*str = temp;
}
