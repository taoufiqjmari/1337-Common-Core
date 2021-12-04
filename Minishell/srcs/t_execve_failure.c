/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_execve_failure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:57:23 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 12:15:37 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	In case execve() fails, execve_failure() func looks for the right error, \
**	it adds './' to the path in case it does not exist and checks what it is \
**	using <sys/stat.h> library macros.
*/

int	file_type(const char *path, int i)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	if (i == 1)
		return (S_ISREG(statbuf.st_mode));
	if (i == 2)
		return (S_ISDIR(statbuf.st_mode));
	else
		return (S_IXUSR & statbuf.st_mode);
}

void	execve_failure(int i)
{
	char		*path;
	char		*spath;

	path = g_tool.cmd[i]->args[0];
	spath = charp_ternary(ft_strchr(path, '/'), path, ft_strjoin("./", path));
	if (file_type(spath, 1))
	{
		if (!file_type(spath, 0))
		{
			ft_puterror("minishell: ", path, ": Permission denied");
			exit(126);
		}
		exit(0);
	}
	else if (file_type(spath, 2))
	{
		ft_puterror("minishell: ", path, ": is a directory");
		exit(126);
	}
	else
	{
		ft_puterror("minishell: ", path, ": No such file or directory");
		exit(127);
	}
}
