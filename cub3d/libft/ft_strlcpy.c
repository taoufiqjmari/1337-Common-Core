/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:40:34 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/19 18:44:47 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	if (size)
	{
		while (src[i] && i < size)
		{
			dst[i] = src[i];
			i++;
		}
		while (i < size)
			dst[i++] = ' ';
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
