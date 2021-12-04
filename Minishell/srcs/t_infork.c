/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_infork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:17:14 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 16:29:56 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Every command is forked for but a built-in that is not in a pipe.
**	ft_waiting() func wait on last cmd of pipe line and set exit_status.
**	run_infork_cases() func is similar to the one in t_executing.c but in fork.
*/

static void	ft_waiting(int i)
{
	if (!(g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|'))
		waitpid(g_tool.pid, &g_tool.exit_status, 0);
	if (WIFSIGNALED(g_tool.exit_status))
	{
		if (!ft_strcmp(g_tool.cmd[g_tool.i]->args[0], "read")
			&& !based_pipe_fork(g_tool.i))
		{
			g_tool.exit_status = 1;
			return ;
		}
		g_tool.exit_status = 128 + WTERMSIG(g_tool.exit_status);
	}
	else
		g_tool.exit_status = WEXITSTATUS(g_tool.exit_status);
}

static void	run_infork_cases(int i)
{
	if (!g_tool.cmd[i]->args && g_tool.cmd[i]->red)
	{
		if (!(set_redirections(g_tool.cmd[i])))
			exit(g_tool.exit_status);
		exit(g_tool.exit_status);
	}
	else if (g_tool.which_builtin)
	{
		if (!(set_redirections(g_tool.cmd[i])))
			exit(g_tool.exit_status);
		run_builtin(i);
		exit(g_tool.exit_status);
	}
	else
	{
		if (!(set_redirections(g_tool.cmd[i])))
			exit(g_tool.exit_status);
		run_cmd_path(i);
	}
}

void	run_infork(int i)
{
	open_pipe(i);
	g_tool.pid = fork();
	ft_waiting(i);
	if (g_tool.pid == 0)
	{
		set_pipe(i);
		run_infork_cases(i);
	}
	close(g_tool.cmd[i]->pipe[1]);
	if (i > 0 && g_tool.cmd[i - 1]->sep && *(g_tool.cmd[i - 1]->sep) == '|')
		close(g_tool.cmd[i - 1]->pipe[0]);
}
