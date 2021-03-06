/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:21:25 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/06 16:32:14 by tjmari           ###   ########.fr       */
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
	int	m;

	i = 1;
	m = n / 10;
	while (m > 0)
	{
		m /= 10;
		i *= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	n2;
	int		i;
	int		s;
	char	*str;

	n2 = n;
	i = 0;
	str = (char *)malloc(sizeof(char) * (number_of_digits(n2) + 1));
	if (!str)
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
