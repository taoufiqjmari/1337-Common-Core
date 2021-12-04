/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_assign.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 17:17:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 13:13:12 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redis(char **sp, int *i, t_cmd **cmds, int cmd_i)
{
	char	**tmp;

	tmp = cmds[cmd_i]->red;
	cmds[cmd_i]->red = append_line(cmds[cmd_i]->red, sp[(*i)], 0);
	doublefree(tmp);
	(*i)++;
	tmp = cmds[cmd_i]->file;
	cmds[cmd_i]->file = append_line(cmds[cmd_i]->file, sp[(*i)], 0);
	doublefree(tmp);
}

static	void	init_cmds(t_cmd	**cmds)
{
	int	i;

	i = 0;
	while (i < g_tool.cmd_c)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		cmds[i]->args = NULL;
		cmds[i]->sep = NULL;
		cmds[i]->red = NULL;
		cmds[i]->file = NULL;
		i++;
	}
}

static	void	next_cmd(char **sp, int i, t_cmd	**cmds, int	*cmd_i)
{
	cmds[(*cmd_i)]->sep = ft_strdup(sp[i]);
	(*cmd_i)++;
}

void	assign(char **sp, int i, int j, int cmd_i)
{
	t_cmd	**cmds;
	char	**tmp;

	g_tool.cmd_c = (count_cmds(sp) + 1);
	cmds = malloc(sizeof(t_cmd *) * (g_tool.cmd_c));
	init_cmds(cmds);
	while (sp[i])
	{
		if (sp[i][j] == '<' || sp[i][j] == '>')
			redis(sp, &i, cmds, cmd_i);
		else if (sp[i][j] == '|' || sp[i][j] == ';')
			next_cmd(sp, i, cmds, &cmd_i);
		else
		{
			tmp = cmds[cmd_i]->args;
			cmds[cmd_i]->args = append_line(cmds[cmd_i]->args, sp[i], 0);
			doublefree(tmp);
		}
		i++;
	}
	g_tool.cmd = cmds;
	doublefree(sp);
}
