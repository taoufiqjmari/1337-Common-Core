/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/04 20:15:23 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	int		pwd;
	char	*tmp;

	g_tool.exit_status = 0;
	pwd = ft_getenv("PWD");
	if (pwd < 0)
		ft_putendl_fd(getcwd(g_tool.cwd, sizeof(g_tool.cwd)), 1);
	else
	{
		tmp = ft_getvalue(g_tool.envp[ft_getenv("PWD")]);
		ft_putendl_fd(tmp, STDIN_FILENO);
		free(tmp);
	}
}
