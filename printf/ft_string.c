/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:27:15 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 15:35:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string_left(char *string, int len)
{
	char	*temp;

	temp = ft_substr(string, 0, len);
	ft_putstr(temp);
	free(temp);
	temp = NULL;
	ft_spaces();
}

/*
** flag '0' results in undefined behavior with 's' conversion specifier
** but mine gives an output with flag '0' following the entire style
*/

void	string_right(char *string, int len)
{
	char	*temp;

	g_vars.zero == 1 ? ft_zeros() : ft_spaces();
	temp = ft_substr(string, 0, len);
	ft_putstr(temp);
	free(temp);
	temp = NULL;
}

/*
** The second if() is for a special case
** ft_printf("%.s", (char *) number);
** ---------------------------------------------
** If there is minus flag, string is ridercted to
** *_left() which refers to left justify,
** otherwise string is redirected to *_right()
*/

void	ft_string(char *string)
{
	int		len;

	if (!string)
		string = "(null)";
	if (g_vars.precision_value == 0 && g_vars.precision != 0)
	{
		g_vars.spaces = g_vars.width;
		ft_spaces();
		ft_putstr("");
	}
	else
	{
		len = ft_strlen(string);
		if (g_vars.precision == 1 && g_vars.precision_value < len)
			len = g_vars.precision_value;
		g_vars.spaces = g_vars.width - len;
		if (g_vars.spaces < 0)
			g_vars.spaces = 0;
		if (g_vars.minus == 1)
			string_left(string, len);
		else
			string_right(string, len);
	}
}
