/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_adfix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:21:35 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 14:06:26 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_spaces(void)
{
	while (g_vars.spaces > 0)
	{
		ft_putchar(' ');
		g_vars.spaces--;
	}
}

void	ft_zeros(void)
{
	while (g_vars.spaces > 0)
	{
		ft_putchar('0');
		g_vars.spaces--;
	}
}

void	ft_zeros_adfix(void)
{
	while (g_vars.zero_adfix > 0)
	{
		ft_putchar('0');
		g_vars.zero_adfix--;
	}
}
