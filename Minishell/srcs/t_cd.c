/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 12:09:32 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	failing_getcwd() func is for the case of \
**	'mkdir dir + cd dir + rm -rf ../dir + cd .'.
**	line 85: for the case 'unset $PATH; cd $PATH'.
*/

static void	change_pwd(int index, char *arg)
{
	free(g_tool.envp[index]);
	g_tool.envp[index] = ft_strdup(arg);
}

static void	failing_getcwd(int i, int pwd)
{
	char	*tmp;
	char	*tmp2;

	ft_puterror("cd: error retrieving current directory: ",
		"getcwd: cannot access parent directories:",
		" No such file or directory");
	tmp = ft_strjoin("/", g_tool.cmd[i]->args[1]);
	tmp2 = ft_strjoin(g_tool.envp[pwd], tmp);
	change_pwd(pwd, tmp2);
	free(tmp);
	free(tmp2);
}

static void	cd_properly(int i, int pwd, int oldpwd)
{
	char	*tmp;
	char	*tmp2;

	if (oldpwd >= 0 && pwd >= 0)
	{
		tmp = ft_getvalue(g_tool.envp[pwd]);
		tmp2 = ft_strjoin("OLDPWD=", tmp);
		change_pwd(oldpwd, tmp2);
		free(tmp);
		free(tmp2);
	}
	if (pwd >= 0)
	{
		if (getcwd(g_tool.cwd, sizeof(g_tool.cwd)))
		{
			tmp = ft_strjoin("PWD=", g_tool.cwd);
			change_pwd(pwd, tmp);
			free(tmp);
		}
		else
			failing_getcwd(i, pwd);
	}
}

void	ft_cd(int i)
{
	int		pwd;
	int		oldpwd;
	char	*tmp;

	g_tool.exit_status = 0;
	pwd = ft_getenv("PWD");
	oldpwd = ft_getenv("OLDPWD");
	if (doublecount(g_tool.cmd[i]->args) == 1)
	{
		ft_puterror("minishell: ", "cd: ",
			"with only a relative or absolute path");
		g_tool.exit_status = 1;
	}
	else if (chdir(g_tool.cmd[i]->args[1]) != 0)
	{
		if (ft_strcmp(g_tool.cmd[i]->args[1], ""))
		{
			tmp = ft_strjoin(": ", strerror(errno));
			ft_puterror("minishell: cd: ", g_tool.cmd[i]->args[1], tmp);
			free(tmp);
		}
		g_tool.exit_status = 1;
	}
	else
		cd_properly(i, pwd, oldpwd);
}
