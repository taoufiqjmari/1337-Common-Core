/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:50 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 17:30:17 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	ft_printexit() func is there because the 'exit' word is printed \
**	before the err msg only if exit is not in fork.
*/

static void	ft_printexit(int i)
{
	if (!((g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|')
			|| (i > 0 && g_tool.cmd[i - 1]->sep
				&& *(g_tool.cmd[i - 1]->sep) == '|')))
		ft_putendl_fd("exit", STDERR_FILENO);
}

static _Bool	ft_isnumeric(char *arg)
{
	if (arg)
	{
		if (*arg == '+' || *arg == '-')
		{
			if (ft_strlen(arg) > 1)
				arg++;
			else
				return (0);
		}
		while (*arg)
		{
			if (*arg >= '0' && *arg <= '9')
				arg++;
			else if (*arg == '\0')
				return (1);
			else
				return (0);
		}
	}
	return (1);
}

static void	check_first_arg(int i)
{
	if (g_tool.cmd[i]->args[1]
		&& !ft_isnumeric(g_tool.cmd[i]->args[1]))
	{
		ft_printexit(i);
		ft_puterror("minishell: exit: ", g_tool.cmd[i]->args[1],
			": numeric argument required");
		exit(255);
	}
}

void	ft_exit(int i)
{
	check_first_arg(i);
	if (doublecount(g_tool.cmd[i]->args) > 2)
	{
		ft_printexit(i);
		ft_puterror("minishell:", " exit:", " too many arguments");
		g_tool.exit_flag = 1;
		g_tool.exit_status = 1;
	}
	else if (ft_isnumeric(g_tool.cmd[i]->args[1]))
	{
		ft_printexit(i);
		if (g_tool.cmd[i]->args[1])
			exit(ft_atoi(g_tool.cmd[i]->args[1]));
		exit(g_tool.exit_status);
	}
	else
	{
		ft_printexit(i);
		ft_puterror("minishell: exit: ", g_tool.cmd[i]->args[1],
			": numeric argument required");
		exit(255);
	}
}
