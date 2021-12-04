/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:33:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/05/28 16:09:41 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

_Bool	based_pipe_fork(int i)
{
	if ((g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|')
		|| (i > 0 && g_tool.cmd[i - 1]->sep
			&& *(g_tool.cmd[i - 1]->sep) == '|'))
		return (1);
	return (0);
}

void	open_pipe(int i)
{
	if (g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|')
		pipe(g_tool.cmd[i]->pipe);
}

void	set_pipe(int i)
{
	if (g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|')
	{
		dup2(g_tool.cmd[i]->pipe[1], STDOUT_FILENO);
		close(g_tool.cmd[i]->pipe[1]);
		close(g_tool.cmd[i]->pipe[0]);
	}
	if (i > 0 && g_tool.cmd[i - 1]->sep && *(g_tool.cmd[i - 1]->sep) == '|')
	{
		dup2(g_tool.cmd[i - 1]->pipe[0], STDIN_FILENO);
		close(g_tool.cmd[i - 1]->pipe[0]);
		close(g_tool.cmd[i - 1]->pipe[1]);
	}
}
