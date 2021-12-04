/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:33:52 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/06 21:02:15 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	signal_int() func for the ctrl-C signal.
**	signal_quit() func for the ctrl-\ signal.
*/

void	signal_int(int sig)
{
	(void)sig;
	if (g_tool.pid)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	ft_putstr_fd("\n\033[0;36mminishell$\033[0m ", STDOUT_FILENO);
	g_tool.exit_status = 1;
	g_tool.trm->h_cur = tgetstr("sc", NULL);
	ft_putstr_fd(g_tool.trm->h_cur, 1);
	if (g_tool.trm->curr)
		free(g_tool.trm->curr);
	g_tool.trm->curr = ft_strdup("");
}

void	signal_quit(int sig)
{
	(void)sig;
	if (g_tool.pid && g_tool.i < g_tool.cmd_c
		&& ft_strcmp(g_tool.cmd[g_tool.i]->args[0], "read"))
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
