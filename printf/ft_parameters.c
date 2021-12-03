/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parameters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:25:23 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 20:34:50 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** It checks flags, width, and precision
** then redirect to specifier()
*/

int		ft_parameters(void)
{
	ft_width();
	ft_precision();
	g_vars.spaces = 0;
	g_vars.zero_adfix = 0;
	g_vars.specifier = *g_vars.str;
	if (*g_vars.str == 'c')
		ft_character();
	else if (*g_vars.str == 's')
		ft_string(va_arg(g_vars.ap, char *));
	else if (*g_vars.str == 'p')
		ft_pointer((unsigned long)va_arg(g_vars.ap, void *));
	else if (*g_vars.str == 'd' || *g_vars.str == 'i')
		ft_integer(va_arg(g_vars.ap, int));
	else if (*g_vars.str == 'u')
		ft_unsigned_int(va_arg(g_vars.ap, int));
	else if (*g_vars.str == 'x' || *g_vars.str == 'X')
		ft_hexadecimal((unsigned int)va_arg(g_vars.ap, int));
	else if (*g_vars.str == '%')
		ft_percent();
	else if (*g_vars.str != 'c' && *g_vars.str != 's' && *g_vars.str != 'p'
		&& *g_vars.str != 'd' && *g_vars.str != 'i' && *g_vars.str != 'u'
		&& *g_vars.str != 'x' && *g_vars.str != 'X' && *g_vars.str != '%')
		return (0);
	g_vars.str++;
	return (1);
}
