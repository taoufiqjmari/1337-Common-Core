/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:34:46 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/13 22:50:13 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_vars.ret++;
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

void	ft_putnbr(int c)
{
	long	num;

	num = c;
	if (num < 0)
		num *= -1;
	if (num > 9)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
		ft_putchar(num + 48);
}

void	ft_putnbr_uint(unsigned int num)
{
	long	num2;

	num2 = num;
	if (num2 > 9)
		ft_putnbr_uint(num2 / 10);
	ft_putchar((num2 % 10 + 48));
}
