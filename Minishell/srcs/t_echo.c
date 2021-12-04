/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:44 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/08 15:12:12 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	line 46: This loop is here to avoid SEGV in empty echo \
**	looping while args exist.
*/

static _Bool	ft_isflag(char *args)
{
	int		i;

	if (!args || ft_isempty(args))
		return (0);
	i = 0;
	if (!(ft_strncmp(args, "-n", 2)))
	{
		i = 2;
		while (args[i] == 'n')
			i++;
	}
	if (!args[i])
		return (1);
	return (0);
}

void	ft_echo(int i)
{
	int		j;
	_Bool	n;

	j = 1;
	n = 0;
	g_tool.exit_status = 0;
	while (j < doublecount(g_tool.cmd[i]->args))
	{
		while (ft_isflag(g_tool.cmd[i]->args[j]))
		{
			n = 1;
			j++;
		}
		while (g_tool.cmd[i]->args[j])
		{
			ft_putstr_fd(g_tool.cmd[i]->args[j], 1);
			if (j != doublecount(g_tool.cmd[i]->args) - 1)
				ft_putstr_fd(" ", 1);
			j++;
		}
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}
