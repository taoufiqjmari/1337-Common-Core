/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:20:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/16 15:03:54 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	The add_node_dc() func adds elements (char *) to (char **).
**	the ft_dcdup() func adds toadd places (char *) to (char **).
*/

void	ft_putexport_cases(char *arg, char *key, char *value)
{	
	if (!ft_strchr(arg, '='))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(key, 1);
	}
	else if (ft_strcmp(value, ""))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putendl_fd("\"", 1);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putendl_fd("\"", 1);
	}
}

char	**ft_dcdup(char **argv, int toadd)
{
	int		i;
	int		len;
	char	**temp;

	i = 0;
	len = doublecount(argv);
	temp = malloc(sizeof(char *) * (len + toadd + 1));
	temp[len + toadd] = NULL;
	while (i < len)
	{
		temp[i] = ft_strdup(argv[i]);
		i++;
	}
	while (i < len + toadd)
	{
		temp[i] = ft_strdup("");
		i++;
	}
	return (temp);
}

static	void	ft_already_exist(char **argv, char *args)
{
	int		index;
	char	*tofree;

	tofree = ft_getvalue(args);
	if (!ft_strcmp(tofree, "") && !ft_strchr(args, '='))
	{
		free(tofree);
		return ;
	}
	free(tofree);
	tofree = ft_getkey(args);
	index = ft_getenv(tofree);
	free(tofree);
	free(argv[index]);
	argv[index] = ft_strdup(args);
}

void	add_node_dc(char **args, int toadd, int envp_len, int args_len)
{
	int		envp_len_h;
	int		i;
	char	*tofree;
	char	*tofree2;
	char	**tmp;

	envp_len_h = envp_len;
	i = 1;
	tmp = g_tool.envp;
	g_tool.envp = ft_dcdup(g_tool.envp, toadd);
	doublefree(tmp);
	while ((envp_len < envp_len_h + args_len) && args[i])
	{
		tofree = ft_getkey(args[i]);
		if (ft_export_valid(args[i]) && ft_getenv(tofree) < 0)
		{
			tofree2 = g_tool.envp[envp_len];
			g_tool.envp[envp_len++] = ft_strdup(args[i]);
			free(tofree2);
		}
		else if (ft_export_valid(args[i]) && ft_getenv(tofree) >= 0)
			ft_already_exist(g_tool.envp, args[i]);
		free(tofree);
		i++;
	}
}
