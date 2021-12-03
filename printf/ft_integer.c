/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:28:29 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 21:15:26 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_len(long num)
{
	int i;

	i = 1;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while ((num = num / 10) > 0)
		i++;
	return (i);
}

void	num_left(int num)
{
	if (num < 0)
	{
		ft_putchar('-');
		num *= -1;
	}
	ft_zeros_adfix();
	ft_putnbr(num);
	ft_spaces();
}

void	num_right(int num)
{
	if (g_vars.zero == 1)
	{
		if (num < 0)
		{
			ft_putchar('-');
			num *= -1;
		}
		ft_zeros();
	}
	else
	{
		ft_spaces();
		if (num < 0)
		{
			ft_putchar('-');
			num *= -1;
		}
	}
	ft_zeros_adfix();
	ft_putnbr(num);
}

void	ft_integer(int num)
{
	int	len;

	len = ft_len(num);
	if (g_vars.precision == 1 && g_vars.precision_value == 0 && num == 0)
	{
		g_vars.spaces = g_vars.width;
		ft_spaces();
		return ;
	}
	if (g_vars.precision == 1)
	{
		g_vars.zero = 0;
		if (g_vars.precision_value >= len)
		{
			if (num < 0)
				g_vars.zero_adfix = g_vars.precision_value - (len - 1);
			else
				g_vars.zero_adfix = g_vars.precision_value - len;
		}
		g_vars.spaces = (g_vars.width - (len + g_vars.zero_adfix));
	}
	else
		g_vars.spaces = g_vars.width - len;
	g_vars.minus == 1 ? num_left(num) : num_right(num);
}
