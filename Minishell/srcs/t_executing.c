/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_executing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:06:48 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/03 17:55:47 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	line 30: for the case 'cmd;', usually the builtin still has the old value \
**	and the 'cmd' get executed twice.
**	line 33: for the case of only '> file'.
**	line 39: for built-ins.
**	line 41: for other cases.
*/

void	executing(void)
{
	g_tool.i = 0;
	while (g_tool.i < g_tool.cmd_c && !g_tool.exit_flag)
	{
		if (g_tool.i > 0 && *(g_tool.cmd[g_tool.i - 1]->sep) == ';')
			finalizem(g_tool.i);
		g_tool.which_builtin = 0;
		if (g_tool.cmd[g_tool.i]->args)
			which_builtin(g_tool.i);
		if (!g_tool.cmd[g_tool.i]->args && g_tool.cmd[g_tool.i]->red
			&& !based_pipe_fork(g_tool.i))
		{
			if (!(set_redirections(g_tool.cmd[g_tool.i])))
				return ;
		}
		else if (g_tool.which_builtin && !based_pipe_fork(g_tool.i))
			run_builtin(g_tool.i);
		else if (g_tool.cmd[g_tool.i]->args || g_tool.cmd[g_tool.i]->red)
			run_infork(g_tool.i);
		reset_std();
		g_tool.i++;
	}
	while (wait(NULL) > 0)
		;
}
