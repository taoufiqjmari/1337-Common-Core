/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:58 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/03 18:31:50 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Look whether the variable is valid, in such case \
**	that element is being freed and the following element \
**	moves backwards and the following one moves backwards \
**	to the place of the one just moved and so on \
**	otherwise an err is printed for the not valid elements.
*/

static int	ft_envremove(char *key)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (g_tool.envp[i])
	{
		if (!ft_strncmp(g_tool.envp[i], key, len)
			&& (g_tool.envp[i][len] == '='
			|| g_tool.envp[i][len] == '\0'))
		{
			j = 0;
			free(g_tool.envp[i]);
			while (g_tool.envp[i + j])
			{
				g_tool.envp[i + j] = g_tool.envp[i + j + 1];
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(int i)
{
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	g_tool.exit_status = 0;
	while (g_tool.cmd[i]->args[j])
	{
		if (ft_strchr(g_tool.cmd[i]->args[j], '=')
			|| !ft_export_valid(g_tool.cmd[i]->args[j]))
		{
			ft_puterror("minishell: unset: `", g_tool.cmd[i]->args[j],
				"': not a valid identifier");
			g_tool.exit_status = 1;
		}
		else
			ft_envremove(g_tool.cmd[i]->args[j]);
		j++;
	}
}
