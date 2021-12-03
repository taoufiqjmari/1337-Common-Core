/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:26:29 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/11 17:50:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_percent(void)
{
	if (g_vars.width > 1)
	{
		g_vars.spaces = g_vars.width - 1;
		if (g_vars.minus == 1)
		{
			ft_putchar('%');
			ft_spaces();
		}
		else
		{
			if (g_vars.zero == 1)
				ft_zeros();
			else
				ft_spaces();
			ft_putchar('%');
		}
	}
	else
		ft_putchar('%');
}
