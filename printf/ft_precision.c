/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:31:12 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 16:14:19 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** It checks if there is precision and holds its value /
** whether it is provided directly or by '*'
*/

void	ft_precision(void)
{
	g_vars.precision = 0;
	g_vars.precision_value = 0;
	if (*g_vars.str == '.')
	{
		g_vars.precision = 1;
		g_vars.str++;
		if (*g_vars.str == '*')
		{
			g_vars.precision_value = va_arg(g_vars.ap, int);
			g_vars.str++;
		}
		while (*g_vars.str >= '0' && *g_vars.str <= '9')
		{
			g_vars.precision_value = (g_vars.precision_value * 10)
			+ (*g_vars.str - 48);
			g_vars.str++;
		}
		if (g_vars.precision_value < 0)
		{
			g_vars.precision = 0;
			g_vars.precision_value = 0;
		}
	}
}
