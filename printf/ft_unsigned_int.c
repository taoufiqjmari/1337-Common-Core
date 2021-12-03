/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:28:50 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/13 22:49:44 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	uint_left(unsigned int num)
{
	ft_zeros_adfix();
	ft_putnbr_uint(num);
	ft_spaces();
}

void	uint_right(unsigned int num)
{
	if (g_vars.zero == 1)
		ft_zeros();
	else
		ft_spaces();
	ft_zeros_adfix();
	ft_putnbr_uint(num);
}

void	ft_unsigned_int(int num)
{
	int				len;
	unsigned int	uint;

	uint = (unsigned int)num;
	len = ft_len(uint);
	if (g_vars.precision == 1 && g_vars.precision_value == 0 && uint == 0)
	{
		g_vars.spaces = g_vars.width;
		ft_spaces();
		return ;
	}
	if (g_vars.precision == 1)
	{
		g_vars.zero = 0;
		if (g_vars.precision_value >= len)
			g_vars.zero_adfix = g_vars.precision_value - len;
		g_vars.spaces = g_vars.width - (len + g_vars.zero_adfix);
	}
	else
		g_vars.spaces = g_vars.width - len;
	g_vars.minus == 1 ? uint_left(uint) : uint_right(uint);
}
