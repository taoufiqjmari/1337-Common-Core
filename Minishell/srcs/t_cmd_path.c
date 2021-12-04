/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:48:54 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/08 15:42:35 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	run_cmd_path() func runs two paths \
**	if the (cmd is a path or there is no path) \
**	and if it's a simple cmd respectively.
*/

static char	*make_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*temp;

	i = 0;
	while (paths[i] && (cmd && cmd[0]))
	{
		tmp = ft_strjoin(paths[i], "/");
		temp = tmp;
		tmp = ft_strjoin(tmp, cmd);
		free(temp);
		if (open(tmp, O_RDONLY) > 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

static void	make_path(int i, char **paths)
{
	char	*cmd;

	cmd = make_cmd(paths, g_tool.cmd[i]->args[0]);
	if (!ft_strcmp(g_tool.cmd[i]->args[0], "."))
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(2);
	}
	else if (cmd && ft_strcmp(g_tool.cmd[i]->args[0], ".."))
		execve(cmd, g_tool.cmd[i]->args, g_tool.envp);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_tool.cmd[i]->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void	run_cmd_path(int i)
{
	int		path_exist;
	char	**paths;

	path_exist = ft_getenv("PATH");
	if (path_exist > -1)
		paths = ft_split(ft_getvalue(g_tool.envp[path_exist]), ':');
	if (ft_strchr(g_tool.cmd[i]->args[0], '/') || path_exist < 0)
	{
		execve(g_tool.cmd[i]->args[0], g_tool.cmd[i]->args, g_tool.envp);
		if (!ft_strcmp(g_tool.cmd[i]->args[0], "."))
		{
			ft_putendl_fd("minishell: .: filename argument required", 2);
			ft_putendl_fd(".: usage: . filename [arguments]", 2);
			exit(2);
		}
		execve_failure(i);
	}
	else
		make_path(i, paths);
}
