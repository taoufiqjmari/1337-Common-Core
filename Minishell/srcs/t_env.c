/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:47 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/16 15:06:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	printing_cases(int i, char *key, char *value)
{
	if (!ft_strchr(g_tool.envp[i], '='))
		return ;
	else if (ft_strcmp(value, ""))
	{	
		ft_putstr_fd(key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(value, 1);
	}
	else
	{
		ft_putstr_fd(key, 1);
		ft_putendl_fd("=", 1);
	}
}

void	ft_env(void)
{
	int		i;
	char	*key;
	char	*value;
	char	*tmp;

	g_tool.exit_status = 0;
	i = 0;
	key = ft_strdup("");
	value = ft_strdup("");
	while (g_tool.envp[i])
	{
		tmp = key;
		key = ft_getkey(g_tool.envp[i]);
		free(tmp);
		tmp = value;
		value = ft_getvalue(g_tool.envp[i]);
		free(tmp);
		printing_cases(i, key, value);
		i++;
	}
	free(key);
	free(value);
}
