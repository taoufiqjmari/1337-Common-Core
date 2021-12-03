/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:21:25 by tjmari            #+#    #+#             */
/*   Updated: 2020/01/31 18:42:53 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_of_digits(long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i++;
		return (i);
	}
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	number_size(long n)
{
	int	i;

	i = 1;
	while ((n /= 10) > 0)
		i *= 10;
	return (i);
}

char		*ft_itoa(int n)
{
	long	n2;
	int		i;
	int		s;
	char	*str;

	n2 = n;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (number_of_digits(n2) + 1))))
		return (NULL);
	s = n2;
	if (s < 0)
	{
		str[i++] = '-';
		n2 *= -1;
	}
	s = number_size(n2);
	while (s)
	{
		str[i++] = (n2 / s) + 48;
		n2 %= s;
		s /= 10;
	}
	str[i++] = '\0';
	return (str);
}
