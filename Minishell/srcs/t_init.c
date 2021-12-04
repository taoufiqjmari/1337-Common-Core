/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:03:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/06 20:52:49 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	the change_shlvl() func increment the shell level if it exists \
**	and it adds it with value 1 if it doesn't exist like in bash.
*/

void	change_shlvl(void)
{
	int		i;
	int		shlvl;
	char	*tofree;
	char	*tofree2;
	char	**parts;

	i = ft_getenv("SHLVL");
	if (i < 0)
	{
		parts = ft_dcdup(g_tool.envp, 1);
		parts[doublecount(g_tool.envp)] = "SHLVL=1";
		doublefree(g_tool.envp);
		g_tool.envp = parts;
		return ;
	}
	tofree = ft_getvalue(g_tool.envp[i]);
	shlvl = ft_atoi(tofree);
	free(tofree);
	tofree = ft_itoa(++shlvl);
	tofree2 = ft_strjoin("SHLVL=", tofree);
	free(tofree);
	free(g_tool.envp[i]);
	g_tool.envp[i] = tofree2;
}

void	unset_oldpwd(void)
{
	int	oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (oldpwd > -1)
	{
		free(g_tool.envp[oldpwd]);
		g_tool.envp[oldpwd] = ft_strdup("OLDPWD");
	}
}
