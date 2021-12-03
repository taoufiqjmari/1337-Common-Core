/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_character.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:27:06 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/11 17:50:03 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_character(void)
{
	if (g_vars.width > 1)
	{
		g_vars.spaces = g_vars.width - 1;
		if (g_vars.minus == 1)
		{
			ft_putchar(va_arg(g_vars.ap, int));
			ft_spaces();
		}
		else
		{
			ft_spaces();
			ft_putchar(va_arg(g_vars.ap, int));
		}
	}
	else
		ft_putchar(va_arg(g_vars.ap, int));
}
