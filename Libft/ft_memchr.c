/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:14:24 by tjmari            #+#    #+#             */
/*   Updated: 2020/01/30 23:17:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s2;

	i = 0;
	s2 = (const unsigned char *)s;
	while (i < n)
	{
		if (s2[i] == (unsigned char)c)
			return ((void *)(s2 + i));
		i++;
	}
	return (0);
}
