/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:06:54 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/02 21:25:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	which_builtin(int i)
{
	if (!ft_strcmp(g_tool.cmd[i]->args[0], "echo"))
		g_tool.which_builtin = 1;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "cd"))
		g_tool.which_builtin = 2;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "pwd"))
		g_tool.which_builtin = 3;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "export"))
		g_tool.which_builtin = 4;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "unset"))
		g_tool.which_builtin = 5;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "env"))
		g_tool.which_builtin = 6;
	else if (!ft_strcmp(g_tool.cmd[i]->args[0], "exit"))
		g_tool.which_builtin = 7;
	else
		g_tool.which_builtin = 0;
}

void	run_builtin(int i)
{
	if (!(set_redirections(g_tool.cmd[i])))
		return ;
	if (g_tool.which_builtin == 1)
		ft_echo(i);
	else if (g_tool.which_builtin == 2)
		ft_cd(i);
	else if (g_tool.which_builtin == 3)
		ft_pwd();
	else if (g_tool.which_builtin == 4)
		ft_export(i);
	else if (g_tool.which_builtin == 5)
		ft_unset(i);
	else if (g_tool.which_builtin == 6)
		ft_env();
	else if (g_tool.which_builtin == 7)
		ft_exit(i);
}
