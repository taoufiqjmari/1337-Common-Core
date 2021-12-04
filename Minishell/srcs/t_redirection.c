/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:51:06 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/03 19:09:19 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_getflag(int i)
{
	if (i == 1)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (i == 2)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (i == 3)
		return (O_RDONLY, S_IRWXU);
	else
		return (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

static void	open_files(t_cmd *cmd, int i)
{
	if (!(ft_strcmp(cmd->red[i], ">")))
		g_tool.fd_out = open(cmd->file[i], ft_getflag(1), ft_getflag(0));
	else if (!(ft_strcmp(cmd->red[i], ">>")))
		g_tool.fd_out = open(cmd->file[i], ft_getflag(2), ft_getflag(0));
	else
		g_tool.fd_in = open(cmd->file[i], ft_getflag(3));
}

static void	affect_std(void)
{
	if (g_tool.fd_out)
		dup2(g_tool.fd_out, STDOUT_FILENO);
	if (g_tool.fd_in)
		dup2(g_tool.fd_in, STDIN_FILENO);
}

_Bool	set_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	g_tool.fd_in = 0;
	g_tool.fd_out = 0;
	while (cmd->red && cmd->red[i])
	{
		open_files(cmd, i);
		if (g_tool.fd_in < 0 || g_tool.fd_out < 0)
		{
			ft_puterror("minishell: ", cmd->file[i],
				": No such file or directory");
			return (0);
		}
		if (cmd->red[i + 1] && g_tool.fd_out && cmd->red[i + 1][0] == '>')
			close(g_tool.fd_out);
		else if (cmd->red[i + 1] && g_tool.fd_in && cmd->red[i + 1][0] == '<')
			close(g_tool.fd_in);
		i++;
	}
	affect_std();
	return (1);
}

void	reset_std(void)
{
	dup2(g_tool.original_fd_in, STDIN_FILENO);
	dup2(g_tool.original_fd_out, STDOUT_FILENO);
}
