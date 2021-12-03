/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:43:32 by tjmari            #+#    #+#             */
/*   Updated: 2020/01/31 20:03:03 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (!*needle || (!*needle && !len))
		return ((char *)haystack);
	if (!len || ft_strlen(haystack) < needle_len)
		return (NULL);
	while (i <= len)
	{
		if ((!(ft_strncmp((haystack + i), needle, needle_len))))
			return ((char *)(haystack + i));
		len--;
		i++;
	}
	return (NULL);
}
