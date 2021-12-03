/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:29:11 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 15:14:43 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hexadecimal_left(char *str)
{
	ft_zeros_adfix();
	ft_putstr(str);
	ft_spaces();
}

void	hexadecimal_right(char *str)
{
	if (g_vars.zero == 1)
		ft_zeros();
	else
		ft_spaces();
	ft_zeros_adfix();
	ft_putstr(str);
}

void	ft_hexadecimal(unsigned int num)
{
	int		len;
	char	*str;

	g_vars.specifier == 'x' ? itox_lower(num, &str) : itox_upper(num, &str);
	len = ft_strlen(str);
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
			g_vars.zero_adfix = g_vars.precision_value - len;
		g_vars.spaces = (g_vars.width - (len + g_vars.zero_adfix));
	}
	else
		g_vars.spaces = g_vars.width - len;
	g_vars.minus == 1 ? hexadecimal_left(str) : hexadecimal_right(str);
	free(str);
}
