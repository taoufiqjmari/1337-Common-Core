/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:51:48 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 16:28:00 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** It prints string till '%' appears then it redirects to ft_parameters()
*/

int		ft_printf(const char *format, ...)
{
	g_vars.ret = 0;
	g_vars.str = (char *)format;
	va_start(g_vars.ap, format);
	while (*g_vars.str)
	{
		if (*g_vars.str == '%')
		{
			g_vars.str++;
			if (!ft_parameters())
				return (0);
		}
		else
		{
			ft_putchar(*g_vars.str);
			g_vars.str++;
		}
	}
	va_end(g_vars.ap);
	return (g_vars.ret);
}
