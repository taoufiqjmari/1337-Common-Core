/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:30:59 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 16:13:15 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(void)
{
	g_vars.minus = 0;
	g_vars.zero = 0;
	while (*g_vars.str == '-' || *g_vars.str == '0')
	{
		if (*g_vars.str == '-')
		{
			g_vars.str++;
			g_vars.minus = 1;
		}
		else if (*g_vars.str == '0')
		{
			g_vars.zero = 1;
			g_vars.str++;
		}
	}
}

/*
** First it checks flags then it holds the value of width /
** weither it is provided directly or by a '*'
*/

void	ft_width(void)
{
	ft_flags();
	g_vars.width = 0;
	if (*g_vars.str == '*')
	{
		g_vars.width = va_arg(g_vars.ap, int);
		g_vars.str++;
	}
	while (*g_vars.str >= '0' && *g_vars.str <= '9')
	{
		g_vars.width = (g_vars.width * 10) + (*g_vars.str - 48);
		g_vars.str++;
	}
	if (g_vars.width < 0)
	{
		g_vars.width *= -1;
		g_vars.minus = 1;
	}
	if (g_vars.minus && g_vars.zero)
		g_vars.zero = 0;
}
