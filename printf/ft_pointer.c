/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:28:01 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 14:07:00 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pointer_case(void)
{
	g_vars.spaces = g_vars.width - 2;
	if (g_vars.minus == 1)
	{
		ft_putstr("0x");
		ft_spaces();
	}
	else
	{
		ft_spaces();
		ft_putstr("0x");
	}
}

void	pointer_left(char *str)
{
	ft_putstr("0x");
	ft_zeros_adfix();
	ft_putstr(str);
	ft_spaces();
}

void	pointer_right(char *str)
{
	if (g_vars.zero == 1)
	{
		ft_putstr("0x");
		ft_zeros();
	}
	else
	{
		ft_spaces();
		ft_putstr("0x");
	}
	ft_zeros_adfix();
	ft_putstr(str);
}

void	ft_pointer(unsigned long pointer)
{
	int		len;
	char	*str;

	if (g_vars.precision == 1 && g_vars.precision_value == 0 && pointer == 0)
	{
		pointer_case();
		return ;
	}
	itox_l_uint(pointer, &str);
	len = ft_strlen(str);
	if (g_vars.precision == 1)
	{
		g_vars.zero = 0;
		if (g_vars.precision_value >= len)
			g_vars.zero_adfix = g_vars.precision_value - len;
		g_vars.spaces = (g_vars.width - (len + g_vars.zero_adfix) - 2);
	}
	else
		g_vars.spaces = g_vars.width - len - 2;
	g_vars.minus == 1 ? pointer_left(str) : pointer_right(str);
	free(str);
	str = NULL;
}
